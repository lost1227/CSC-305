package com.cstaley.patterns.proxy;

import java.util.Collection;
import java.util.Iterator;

public class ROCollection implements Collection {
   private Collection trg;
   
   public ROCollection(Collection trg) {
      this.trg = trg;
   }
   
   @Override
   public boolean add(Object arg0) {
      throw new UnsupportedOperationException();
   }

   @Override
   public boolean addAll(Collection arg0) {
      throw new UnsupportedOperationException();
   }

   @Override
   public void clear() {
      throw new UnsupportedOperationException();
   }

   @Override
   public boolean contains(Object val) {
      return trg.contains(val);
   }

   @Override
   public boolean containsAll(Collection val) {
      return trg.containsAll(val);
   }

   @Override
   public boolean isEmpty() {
      return trg.isEmpty();
   }

   @Override
   public Iterator iterator() {
      return trg.iterator();
   }

   @Override
   public boolean remove(Object arg0) {
      throw new UnsupportedOperationException();
   }

   @Override
   public boolean removeAll(Collection arg0) {
      throw new UnsupportedOperationException();
   }

   @Override
   public boolean retainAll(Collection arg0) {
      throw new UnsupportedOperationException();
   }

   @Override
   public int size() {
      return trg.size();
   }

   @Override
   public Object[] toArray() {
      return trg.toArray();
   }

   @Override
   public Object[] toArray(Object[] arr) {
      return trg.toArray(arr);
   }
}
