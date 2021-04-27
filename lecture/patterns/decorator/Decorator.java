package com.cstaley.patterns.decorator;

public abstract class Decorator implements MsgMaker {

   protected MsgMaker next;

   public Decorator(MsgMaker next) {
      super();
      this.next = next;
   }

   @Override
   public boolean isEOF() {
      return next.isEOF();
   }

}