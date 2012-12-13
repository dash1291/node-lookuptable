#include <map>

#include <node.h>
#include "lookuptable.h"

using namespace v8;

LookupTable::LookupTable(){};

void LookupTable::Init(Handle<Object> target) {
	// Define constructor
	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	t->SetClassName(String::NewSymbol("LookupTable"));
	t->InstanceTemplate()->SetInternalFieldCount(5);

	// Define prototype
	t->PrototypeTemplate()->Set(String::NewSymbol("insert"),
		FunctionTemplate::New(Insert)->GetFunction());
	t->PrototypeTemplate()->Set(String::NewSymbol("lookup"),
		FunctionTemplate::New(Lookup)->GetFunction());
	t->PrototypeTemplate()->Set(String::NewSymbol("get"),
		FunctionTemplate::New(Get)->GetFunction());
	t->PrototypeTemplate()->Set(String::NewSymbol("remove"),
		FunctionTemplate::New(Remove)->GetFunction());
	t->PrototypeTemplate()->Set(String::NewSymbol("length"),
		FunctionTemplate::New(Length)->GetFunction());

	// Layer the constructor
	Persistent<Function> constructor = Persistent<Function>::New(t->GetFunction());
	target->Set(String::NewSymbol("LookupTable"), constructor);
}

Handle<Value> LookupTable::New(const Arguments& args) {
	LookupTable *newObj = new LookupTable();
	newObj->Wrap(args.This());

	return args.This();
}

Handle<Value> LookupTable::Get(const Arguments& args) {
	HandleScope scope;

	LookupTable *thisObj = ObjectWrap::Unwrap<LookupTable>(args.This());
	int index = args[0]->IntegerValue();
	std::map<std::string, std::string> element = thisObj->array[index];

	Local<Object> obj = Object::New();
	// Iterate over the map keys and build a JS object and return it
	for( std::map<std::string, std::string>::iterator ii=element.begin(); ii!=element.end(); ++ii) {
    	obj->Set(String::NewSymbol((*ii).first.c_str()), String::NewSymbol((*ii).second.c_str()));
   	}
   	return scope.Close(obj);
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
		thisObj->indices[*keyStr].ind[*valStr] = (int)thisObj->array.size();
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

// Removes an element from given index - goes as .remove(index) in JS.
Handle<Value> LookupTable::Remove(const Arguments& args) {
	HandleScope scope;

	LookupTable *thisObj = ObjectWrap::Unwrap<LookupTable>(args.This());
	int index = args[0]->IntegerValue();
	std::map<std::string, std::string> element = thisObj->array[index];

	// Remove a pair from the index map for every key found in the element to be removed.
	for(std::map<std::string, std::string>::iterator ii=element.begin(); ii!=element.end(); ++ii) {
		thisObj->indices[(*ii).first.c_str()].ind.erase((*ii).second.c_str());
		if(thisObj->indices[(*ii).first.c_str()].ind.empty()) {
			thisObj->indices.erase((*ii).first.c_str());
		}
   	}
	thisObj->array.erase(thisObj->array.begin() + index);
}

// Get the length of the table - goes as .length() in JS.
Handle<Value> LookupTable::Length(const Arguments& args) {
	HandleScope scope;

	LookupTable *thisObj = ObjectWrap::Unwrap<LookupTable>(args.This());
	int len = thisObj->array.size();

	return scope.Close(Number::New(len));
}

void LookupTable::PrepareIndices() {
	// TODO
}

NODE_MODULE(lookuptable, LookupTable::Init);
