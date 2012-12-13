LookupTable = require('./build/Release/lookuptable').LookupTable;

var lt = new LookupTable();
lt.insert({'name': 'ashish'});
lt.insert({'name': 'ashish2'});
lt.insert({'name': 'ashish3', 'last': 'dubey'});

console.log(lt.lookup('name', 'ashish3')) // 2
console.log(lt.get(0)) // { name: 'ashish' }