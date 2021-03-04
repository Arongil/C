# Background

Hashtables are used everywhere to create constant-time read, write, and search functionality. Super useful! This document contains the requisite background to hashtables.

## Hash function

A hash function is some function f that reduces data of arbitrary length to a fixed-size value, typically some number of bytes. Some examples of hash functions for a string would be:
- Return sum of all ASCII values of characters in the string.
- Return the length of the string.
- Return number mod 1000.

However, we want a number of qualities for our hash function.
1) **Deterministic** -- if we hash the same data twice, it must hash to the same value. As a consequence, if f(a) = f(b), then possibly a = b. If f(a) !== f(b), then definitely a !== b.
2) **One-way** -- there is no straightforward way to get back the original data that resulted in the hash.
3) **Sensitive** -- if a single bit changes in the input, the entire hash should change to something unrelated to the original hash.

The SHA family of hashes (Secure Hash Algorithm) is frequently used. It's a complex algorithm that tries to ensure that single-bit changes in the input result in total changes to the output.

## Applications: Data integrity checks

How do you know you downloaded the right file? You can hash the original file and provide the correct hash; then if the hash you receive after downloading is different, you may have downloaded malware!

## Applications: Password checks

Storing plaintext passwords is a bad idea. Instead, databases often store a hash of the password, which the website checks against a hashed version of whatever the user types in. Sometimes websites also *salt* the hash, for example by storing `hash(password + username)`. That way, if the database is leaked, the hacker may not come away with anything useful.

## Caution: collisions

One of the dangers of hashes is when f(a) = f(b) for a !== b. These are called *collisions* and are dangerous in the real world. That's why, for secure purposes, we care a lot about the mathematical specifics of the hash algorithms.

# Dictionaries

Our goal is to design an O(1) read-write structure of keys and values. Most dictionaries are implemented with hash tables or hash maps. There are many, many variations on this idea. We'll go through one using *separate chaining* with a *fixed bucket size*.

Goals:
1) Collection of keys, each with an associated value.
2) Able to quickly look up if a key is in the collection and fetch associated value.
3) Able to easily add and remove key-value pairs.

Idea: hash keys to look up a key-value pair. Then use hash values as indices in a big array. It's a common tradeoff: memory for speed.

## Bare-bones example

First, a struct:

```
typedef struct {
    const char *key;
    int value;
} key_value_pair;

uint8_t string_hash(const char *s) {
    return (uint8_t)strlen(s);
}

key_value_pair *entries = calloc(256, sizeof(key_value_pair));

key_value_pair *lookup(key_value_pair *entries, const char *key) {
    uint8_t hash = string_hash(key);
    key_value_pair *entry = &entries[hash];

    if (entry->key == NULL) {
        return NULL;
    } else {
        return entry;
    }
}

void add(key_value_pair *entries, const char *key, int value) {
    uint8_t hash = string_hash(key);
    entries[hash].key = key;
    entries[hash].value = value;
}

void remove(key_value_pair *entries, const char *key, int value) {
    uint8_t hash = string_hash(key);
    if (lookup(entries, key) != NULL) {
        entries[hash].key = NULL;
        entries[hash].value = NULL;
    }
}
```

Issues:
1) What to do about hash collisions?
2) What about bigger hashes?

Solution: map hash values to a linked list of key-value pairs.

This is where implementations begin to diverge. We put these hash values in *buckets*.

```
typedef kvp {
    const char *key;
    int value;

    struct kvp next;
} kvp;

kvp *lookup(kvp_node *buckets, const char *key) {
    uint8_t hash = string_hash(key);

    kvp *bucket_head = &buckets[hash];
    kvp *current_node = bucket_head;

    while (current_node != NULL) {
        if (strcmp(current_node->key, key) == 0) {
            return current_node;
        }
        current_node = current_node->next;
    }
    
    return NULL;
}
```

A word on the performance. Lookups are no longer O(1), since we have to search through the linked list in O(n) time. However, a good hash function and a large enough array will cause a good spread. With 1000 buckets, a hashtable may never have more than 10 values in a given bucket, which makes the search mostly constant time. The hashtable is a sophisticated way to divide the search time by a factor which is how much memory we give it.
