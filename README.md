Lookup Table
------------

This is part of my expedition to learning to write Node.js modules in C++.

Lookup Table helps in fast lookups on an array of objects/associative arrays. Lookup Table achieves this with the help of indexing on all the fields that is keys in individual elements of the array. 

For example, if you have an array in JavaScript:

```javascript
var array = [
	{'firstname': 'first1', 'lastname': 'last1'},
	{'firstname': 'first2', 'lastname': 'last2'},
	{'firstname': 'first3', 'lastname': 'last3'}
]
```

Say, you wanted to lookup a record in this array where 'firstname=first3'. Using lookup table, you can find the record in hashing like efficiency.

Compiling
=========

```
npm build .
```