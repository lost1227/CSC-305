package com.cstaley.patterns.adapter;

public class Test {
   public static void main(String[] args) { 
      StackAdapter<Integer> stk
       = new StackAdapter<Integer>(new java.util.Stack<Integer>());
   
      stk.push(1).push(2).push(3);
      while (!stk.isEmpty()) {
         System.out.println(stk.top());
         stk.pop();
      }
   }
}
