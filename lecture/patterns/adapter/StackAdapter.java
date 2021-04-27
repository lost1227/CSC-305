package com.cstaley.patterns.adapter;

public class StackAdapter<T> implements Stack<T> {
   private java.util.Stack<T> libStack;
   
   public StackAdapter(java.util.Stack<T> stk) {libStack = stk;}

   @Override public Stack<T> push(T val)  {libStack.push(val); return this;}
   @Override public void pop()            {libStack.pop();}
   @Override public boolean isEmpty()     {return libStack.empty();}
   @Override public T top()               {return libStack.peek();}
}
