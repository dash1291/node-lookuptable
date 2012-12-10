#include <node.h>
#include "lookuptable.h"

using namespace v8;

void LookupTable::Init(Handle<Object> target) {
	// Define constructor
	Local<FunctionTemplate> t = FunctionTemplate::New(New);
	t->SetClassName(String::NewSymbol("LookupTable"));
	t->InstanceTemplate()->SetInternalFieldCount(2);

	// Define prototype
	t->PrototypeTemplate()->Set(String::NewSymbol("push"),
		FunctionTemplate::New(Push)->GetFunction());
	t->PrototypeTemplate()->Set(String::NewSymbol("push"),
		FunctionTemplate::New(Push)->GetFunction());

	// Layer the constructor
	Persistent<Function> constructor = Persistent<Function>::New(t->GetFunction());
	target->Set(String::NewSymbol("LookupTable"), constructor);
}

Handle<Value> LookupTable::Push(const Arguments& args) {
	HandleScope scope;
}

Handle<Value> LookupTable::Lookup(const Arguments& args){
	HandleScope scope;

	// This is the first param(lookupField)
	String lookupField = args[0];
	// The key to lookup
	String key = args[1];
}

NODE_MODULE(lookuptable, LookupTable::Init);
