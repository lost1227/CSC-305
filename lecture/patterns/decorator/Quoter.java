package com.cstaley.patterns.decorator;

public class Quoter extends Decorator {
   public Quoter(MsgMaker next) {
      super(next);
   }

   @Override
   public String getMsg() {
      return "'" + next.getMsg() + "'";
   }
}
