package com.cstaley.patterns.decorator;

public class SimonSezer extends Decorator {
   public SimonSezer(MsgMaker next) {
      super(next);
   }

   @Override
   public String getMsg() {
      return "Simon says: " + next.getMsg();
   }
}
