package com.cstaley.patterns.bridge;

import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.io.Writer;

public class Main {
   public static void drawLetters(Letter[] ltrs) {
      for (Letter ltr: ltrs)
         ltr.draw();
   }
   
   public static void main(String[] args) {
      Writer sysOut = new OutputStreamWriter(System.out);
      Writer strOut = new StringWriter();
      
      new PrintWriter(System.out).println("TEST");
      
      Letter letters[] = {
         new LetterA(sysOut),
         new LetterC(sysOut),
         new LetterA(sysOut)
      };
      
      Letter strLetters[] = {
         new LetterA(strOut),
         new LetterC(strOut),
         new LetterA(strOut)
      };
      
      drawLetters(letters);  // to System.out
      drawLetters(strLetters); // to String
      
      // System.out.printf("String has:\n%s\n", strOut);
   }
}
