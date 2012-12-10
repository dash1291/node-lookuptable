#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H

#include <node.h>

#include <map>

using namespace v8;

class LookupTable : public node::ObjectWrap {
public:
	static v8::Persistent<v8::FunctionTemplate> constructor;
	static void Init(v8::Handle<v8::Object> target);

protected:
	LookupTable(const v8::Arguments& args);

	static v8::Handle<v8::Value> Value(const v8::Arguments& args);
	v8::Handle<v8::Value> Push(const v8::Arguments& args);
	v8:Handle<v8::Value> Lookup(const v8::Arguments& args);

	map<String, String> array;
};

#endif