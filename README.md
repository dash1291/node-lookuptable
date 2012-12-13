Lookup Table
------------

This is part of my expedition to learning to write Node.js modules in C++.

Lookup Table helps in fast lookups on an array of objects/associative arrays. Its motive is similar to IndexedDB where one can do fast lookups because of indexing on fields. Lookup Table also achieves fast lookups with the help of indexing on all the fields. 

For example, if you have an array in JavaScript like this:

```javascript
var array = [
	{'firstname': 'first1', 'lastname': 'last1'},
	{'firstname': 'first2', 'lastname': 'last2'},
	{'firstname': 'first3', 'lastname': 'last3'}
]
```

This is like an in-memory table. Say, you wanted to lookup a record in this array where 'firstname=first3'. In the naive approach, you would do a linear search over the array. Pretty straightforward, but hurts in situations where you have thousands of records in the array. Thanks to the lookup table and its indexing, you can find a record in hashing like efficiency.

Compiling
=========

```
npm build .
```