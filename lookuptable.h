#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H

#include <node.h>

#include <map>
#include <tr1/unordered_map>
#include <vector>

typedef struct lookupkey {
	std::tr1::unordered_map<std::string, int> ind;
} lookupkey;

class LookupTable : public node::ObjectWrap {
public:
	static v8::Persistent<v8::Function> constructor;
	static void Init(v8::Handle<v8::Object> target);

protected:
	LookupTable();

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> Insert(const v8::Arguments& args);
	static v8::Handle<v8::Value> Lookup(const v8::Arguments& args);
	static v8::Handle<v8::Value> Get(const v8::Arguments& args);
	static v8::Handle<v8::Value> Remove(const v8::Arguments& args);
	static v8::Handle<v8::Value> Length(const v8::Arguments& args);
	
	void PrepareIndices();

private:
	std::vector<std::map<std::string, std::string> > array;
	std::tr1::unordered_map<std::string, lookupkey> indices;
};

#endif
