#include <map>

#include <node.h>
#include "lookuptable.h"

using namespace v8;

LookupTable::LookupTable(){};

void LookupTable::Init(Handle<Object> target) {
	// Define constructor
	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	t->SetClassName(String::NewSymbol("LookupTable"));
	t->InstanceTemplate()->SetInternalFieldCount(2);

	// Define prototype
	t->PrototypeTemplate()->Set(String::NewSymbol("insert"),
		FunctionTemplate::New(Insert)->GetFunction());
	t->PrototypeTemplate()->Set(String::NewSymbol("lookup"),
		FunctionTemplate::New(Lookup)->GetFunction());

	// Layer the constructor
	Persistent<Function> constructor = Persistent<Function>::New(t->GetFunction());
	target->Set(String::NewSymbol("LookupTable"), constructor);
}

Handle<Value> LookupTable::New(const Arguments& args) {
	LookupTable *newObj = new LookupTable();
	newObj->Wrap(args.This());

	return args.This();
}

// This method handles the inserts - goes as the .insert(Object element) method in JS.
Handle<Value> LookupTable::Insert(const Arguments& args) {
	HandleScope scope;
	
	LookupTable *thisObj = ObjectWrap::Unwrap<LookupTable>(args.This());

	Handle<Object> obj = args[0]->ToObject();
	Local<Array> props = obj->GetPropertyNames();

	int i = 0;

	// This map will form a single element in the array(table).
	std::map<std::string, std::string> itemMap;

	// Iterate over the keys in the supplied object(associative array).
	while(i < props->Length()) {
		// Get the key name and convert it into a C++ usable string.
		Local<String> key = props->Get(Integer::New(i))->ToString();
		String::AsciiValue keyStr(key);

		// Get the value for the key.
		Local<String> val = obj->Get(key)->ToString();
		String::AsciiValue valStr(val);

		// Create the key-value pair in the map.
		itemMap[*keyStr] = *valStr;

		// Use the lookupkey structure to store to index.
		// Uses two level maps. Stores the fields in the first level, and
		// stores the values-element offset pair in the second level.
		lookupkey lk;
		lk.ind[*valStr] = (int)thisObj->array.size();
		thisObj->indices[*keyStr] = lk;
		i++;
	}
	// Insert the element map into our array vector.
	thisObj->array.push_back(itemMap);
}

// Method to lookup a particular record in the table - goes as .lookup(field, key) in JS.
Handle<Value> LookupTable::Lookup(const Arguments& args) {
	HandleScope scope;

	LookupTable *thisObj = ObjectWrap::Unwrap<LookupTable>(args.This());
	
	// This is the first param(lookupField)
	String::AsciiValue field(args[0]->ToString());
	// The key to lookup
	String::AsciiValue key(args[1]->ToString());

	return scope.Close(Number::New(thisObj->indices[*field].ind[*key]));
}

void LookupTable::PrepareIndices() {
	// TODO
}

NODE_MODULE(lookuptable, LookupTable::Init);
