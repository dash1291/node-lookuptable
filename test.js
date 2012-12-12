lookup = require('./build/Release/lookuptable').LookupTable;

var x = new lookup();
x.insert({'name': 'ashish'});
x.insert({'name': 'ashish2'});
console.log(x.lookup('name', 'ashish2'));