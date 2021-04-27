package com.cstaley.patterns.decorator;

import java.util.Scanner;

public class Main {

   public static void main(String[] args) {
      // MsgMaker mkr = new Capitalizer(new MsgSource(new Scanner(System.in)));
      MsgMaker mkr = new Quoter(new Capitalizer(new SimonSezer(
       new MsgSource(new Scanner(System.in)))));
      
      while (!mkr.isEOF())
         System.out.println(mkr.getMsg());
   }
}
