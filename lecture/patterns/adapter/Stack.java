package com.cstaley.patterns.adapter;

public interface Stack<T> {
   Stack<T> push(T val);  // Push val and return the stack for chaining.
   void pop();            // Pop off val, but don't return it
   boolean isEmpty();     // Is stack empty?
   T top();               // Return top element of stack
}
