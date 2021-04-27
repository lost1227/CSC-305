package com.cstaley.patterns.bridge;

import java.io.OutputStream;
import java.io.Writer;

public class LetterA extends Letter {

   public LetterA(Writer out) {
      super(out);
   }

   @Override
   public void drawLetter() {
      out.println("**");
      out.println(" **");
      out.println(" * *");
      out.println(" **");
      out.println("**");
   }
}
