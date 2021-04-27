package com.cstaley.patterns.decorator;

public class Capitalizer extends Decorator {
   public Capitalizer(MsgMaker next) {
      super(next);
   }

   @Override
   public String getMsg() {
      return next.getMsg().toUpperCase();
   }
   
}
