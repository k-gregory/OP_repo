package io.github.atommed.ads;

import java.util.*;
import java.util.function.BiFunction;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class HashMap<K,V>{
    final static private int initialCapacity = 1 << 4;
    static private double defaultLoadFactor = 0.75;
    private double loadFactor;

    private static class Bucket<K,V>{
        K key;
        V value;
        boolean used;

        public K getKey() {
            return key;
        }

        public V getValue() {
            return value;
        }

        public V setValue(V v) {
            V old = this.value;
            this.value = v;
            return old;
        }

        private Bucket(K key, V value, boolean used) {
            this.key = key;
            this.value = value;
            this.used = used;
        }
    }

    private void initTable(){
        for(int i = 0; i < capacity; i++)
            table[i] = new Bucket<>(null,null, false);
    }

    public HashMap(int initialCapacity, double loadFactor) {
        int capacity = HashMap.initialCapacity;
        while(capacity < initialCapacity) capacity*=2;

        table = new Bucket[capacity];
        this.capacity = capacity;
        this.loadFactor = loadFactor;
        initTable();
    }

    public HashMap(int initialCapacity){
        this(initialCapacity, HashMap.defaultLoadFactor);
    }

    public HashMap(){
        this(HashMap.initialCapacity,HashMap.defaultLoadFactor);
    }

    public int size() {
        return size;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public boolean containsKey(Object o) {
        Bucket<K,V> bucket = getBucket(o, true);
        return bucket != null;
    }

    private Bucket<K, V> getBucket(Object key, boolean used){
        final BiFunction<Object, K, Boolean> eq;
        final Predicate<Bucket<K,V>> suitable;

        int startPos;
        if(key == null){
            eq = (testedKey, bucketKey) -> bucketKey == null;
            startPos = 0;
        }
        else{
            startPos = indexFor(key.hashCode());
            eq = Object::equals;
        }

        if(used){
            suitable = kvBucket -> kvBucket.used && eq.apply(key, kvBucket.key);
        }
        else suitable = kvBucket -> !kvBucket.used;

        Optional<Bucket<K,V>> bucket;

        bucket = Arrays.stream(table,startPos,capacity).filter(suitable).findFirst();
        if(bucket.isPresent()) return bucket.get();
        bucket = Arrays.stream(table,0,startPos).filter(suitable).findFirst();
        if(bucket.isPresent()) return bucket.get();

        return null;
    }

    public V get(Object key) {
        Bucket<K,V> bucket = getBucket(key, true);

        if(bucket != null) return bucket.value;
        else {
            return null;
        }
    }

    private void grow(){
        Bucket<K,V>[] oldTable = this.table;
        capacity = capacity * 2;
        this.table = new Bucket[capacity];
        initTable();
        this.size = 0;

        for (Bucket<K,V> kvBucket : oldTable)
            put(kvBucket.getKey(), kvBucket.getValue());
    }

    public V put(K key, V value) {
        BiFunction<K,K,Boolean> eq;
        Bucket<K,V> bucket = null;
        int startPos = 0;

        if(size+1/capacity > loadFactor) grow();

        eq = key == null ? (k1,k2) -> k1 == k2 : (k1,k2)->k1.equals(k2);
        if(key!=null) startPos = indexFor(key.hashCode());

        for(int i = startPos; i < capacity; i++)
            if(table[i].used && eq.apply(key, table[i].key) || !table[i].used) {
                bucket = table[i];
                break;
            }
        for(int i = 0; i < startPos; i++)
            if(table[i].used && eq.apply(key, table[i].key) || !table[i].used) {
                bucket = table[i];
                break;
            }

        if(!bucket.used) size++;
        bucket.used = true;
        bucket.key = key;
        return bucket.setValue(value);
    }

    public V remove(Object key) {
        Bucket<K,V> bucket = getBucket(key, true);
        if(bucket!=null){
            bucket.used = false;
            bucket.key = null;
            size--;
            return bucket.setValue(null);
        } else return null;
    }


    private int indexFor(int hashCode){
        return  hashCode & (this.capacity - 1);
    }


    private int size;
    private int capacity;
    private Bucket<K,V>[] table;

}