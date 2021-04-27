package com.cstaley.patterns.decorator;

import java.util.Scanner;

public class MsgSource implements MsgMaker {
   private Scanner src;
   
   public MsgSource(Scanner src) {
      super();
      this.src = src;
   }

   @Override
   public String getMsg() {
      return src.nextLine();
   }

   @Override
   public boolean isEOF() {
      return !src.hasNextLine();
   }
}
