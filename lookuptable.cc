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

Handle<Value> LookupTable::Insert(const Arguments& args) {
	HandleScope scope;
	
	LookupTable *thisObj = ObjectWrap::Unwrap<LookupTable>(args.This());

	Handle<Object> obj = args[0]->ToObject();
	Local<Array> props = obj->GetPropertyNames();

	int i = 0;
	std::map<std::string, std::string> itemMap;
	while(i < props->Length()) {
		Local<String> key = props->Get(Integer::New(i))->ToString();
		String::AsciiValue keyStr(key);

		Local<String> val = obj->Get(key)->ToString();
		String::AsciiValue valStr(val);

		itemMap[*keyStr] = *valStr;

		lookupkey lk;
		lk.ind[*valStr] = (int)thisObj->array.size();
		thisObj->indices[*keyStr] = lk;
		i++;
	}
	thisObj->array.push_back(itemMap);
}

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
	
}

NODE_MODULE(lookuptable, LookupTable::Init);
