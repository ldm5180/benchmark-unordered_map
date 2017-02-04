# Purpose

This benchmark is to display that inserts into a pre-allocated
```std::unordered_map`` are roughly constant time given no hash
collisions.

The keys are unique uint64s which are all less than the size of the
map. Therefore, they will all hash to a unique bucket.

In addition, removing elements so that the map has a lower load factor
does not change the time to insert a new element. It does decrease the
likelihood of collisions in the case that the keys can hash to the
same bucket.

# Methodology

Pre-allocate (```std::unordered_map::reserve()```) an unordered_map of
10 million elements and set the load factor to 10,000 to avoid the
possibility of ever rehashing.

1. Insert 5 million elements, then another 5 million. Time each set.
1. Insert 5 million elements, remove them, insert a different 5
   million. Time each set.

# Conclusion

1. There is no detectable difference between the first and second sets
   of 5 million.
1. There is no detectable difference between the additions of the
sets, and the removals add time to the toal test.

### Raw output data

```
Insert test:
  Num buckets: 10352717
  Load factor: 0.96593
  Time to input 0-5mm: 258767 ms
  Time to input 5-10mm: 255895 ms

Removals test:
  Num buckets: 10352717
  Load factor: 0.96593
  Time to input 0-5mm:     224215 ms
  Time to remove 0-5mm:    125949 ms
  Time to input 5-10mm:    182474 ms
  Time to input 0-5mm (2): 259165 ms
```

Notice, the addition of the removals only adds more total time (and
clock cycles, presumeably but not measured here). If it is possible in
your application, you could avoid the removals and not impact
insertion time.

There are many more parts of this to investigate. For example:
- what happens when there are collisions?
- why are inserts so fast after the removals?

Remember, there are cache effects which are playing tricks with your
head in this microbenchmark.
