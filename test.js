LookupTable = require('./build/Release/lookuptable').LookupTable;

var lt = new LookupTable();
lt.insert({'name': 'ashish'});
lt.insert({'name': 'ashish3'});
lt.insert({'name': 'ashish32'});
lt.insert({'name': 'ashish31', 'last': 'dubey'});

console.log(lt.lookup('name', 'ashish3')) // 2
console.log(lt.get(2)) // { name: 'ashish32' }
lt.remove(2);
console.log(lt.length()); // 3
