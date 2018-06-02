/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Random Testing is added by Chieko Duncans
 * Reference: https://stackoverflow.com/questions/39222044/generate-random-string-in-java
 */
import java.security.SecureRandom;
import java.util.Random;

import junit.framework.TestCase;

/**
 * Performs Validation Test for url-validations.
 *
 * @version $Revision: 1739358 $
 */
public class UrlValidatorTest extends TestCase {

   private static final int MAX_UNSIGNED_16_BIT_INT = 0;
   private final boolean printStatus = false;
   private final boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   @Override
protected void setUp() {
      for (int index = 0; index < testPartsIndex.length - 1; index++) {
         testPartsIndex[index] = 0;
      }
   }
   
   /*
    * create URL string with each parts
    * {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
    */
   protected String createRandAlpha(int length) {
	   
	    String alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	    
	        Random random = new SecureRandom();
	        if (length <= 0) {
	            throw new IllegalArgumentException("String length must be a positive integer");
	        }

	        StringBuilder sb = new StringBuilder(length);
	        for (int i = 0; i < length; i++) {
	            sb.append(alpha.charAt(random.nextInt(alpha.length())));
	        }


	   return sb.toString();
   }
   
   protected String createRandAlphaNum(int length, boolean withSlash) {
	   
	   String alpha;
	   alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	   
       Random random = new SecureRandom();
       if (length <= 0) {
           throw new IllegalArgumentException("String length must be a positive integer");
       }
       
       StringBuilder sb = new StringBuilder(length);
       
	   if(withSlash) {
		   int counter = 0;
	        for (int i = 0; i < length; i++) {
	            sb.append(alpha.charAt(random.nextInt(alpha.length())));
	            
	            if(counter == (length % 5) + 5) {
	            	sb.append("/");
	            	length++;
	            	counter = 0;
	            }
	        } 
	   }
	   else {
	        for (int i = 0; i < length; i++) {
	            sb.append(alpha.charAt(random.nextInt(alpha.length())));
	        } 
	   } 
	   return sb.toString();
  }
   
   protected String createRandNum(int min, int max) {
	    
	        Random rand = new SecureRandom();
	 	    int num = rand.nextInt(max - min) + min;

	   return String.valueOf(num);
 }
   
   protected String createRandScheme() {
	   // valid "Alpha + (Alnum | + | - | . )
	   
	   // get random length of Scheme
	   Random rand = new SecureRandom();
	   
	   // length - 1 of Scheme
	   int num = rand.nextInt((10 - 3) + 1) + 3;

	   return (createRandAlpha(1) + createRandAlphaNum(num, false) + "://");
   }
   
   protected String createRandAuthority() {
	   
	   // get random length of Scheme
	   Random rand = new SecureRandom();
	   
	   // create 3 choices
	   int num = rand.nextInt(3);
	   
	   // 0) ***.***.*** 
	   // iPort < 0 || iPort > MAX_UNSIGNED_16_BIT_INT  , then error
	   
	   
	   // 1) ********.**
	   // 2) ********.***
	   
	   
	   if(num == 0) {
		  return (createRandNum(0, 255) + "." + createRandNum(0, 255) 
				  + "." + createRandNum(0, 255) + "." + createRandNum(0, 255)) ;
	   }
	   else if(num == 1){
		 // return (createRandAlpha(10) + "." + createRandAlpha(2));
		   return ("lllaaa" + "." + "au");
	   }
	   else {
		 //  	String temp = (createRandAlpha(10) + "." + createRandAlpha(3));
		   	String temp = (createRandAlpha(10).toLowerCase() + "." + "com");
		   //	String temp = (createRandAlpha(10).toLowerCase() + "." + createRandAlpha(3).toLowerCase());


		   //	System.err.println(temp);
		   	return temp;
			 // return (createRandAlpha(10) + "." + createRandAlpha(3));
			  //return ("lllaaa" + "." + "com");

	   }
	   
   }
   protected String createRandPort() {
	   Random rand = new SecureRandom();
	   
	   // set null or not for port number
	   int num = rand.nextInt(2);
	   
	   if(num == 0) { 
		   return "";
	   }
	   else {
		   return (":" + createRandNum(1, 65535));
	   }
   }
   protected String createRandPath() {
	   Random rand = new SecureRandom();
	   
	   // set null or not for port number
	   int num = rand.nextInt(30);
	   
	   
	   if(num == 0) { 
		   return "";
	   }
	   else {
		   return ("/" + createRandAlpha(1) + createRandAlphaNum(num, true));
	   }
   }
   protected String createRandQuery() {
	   return "?action=view";
   }
   protected String createRandURL() {
	   
	   return (createRandScheme() + createRandAuthority() + 
			   createRandPort() + createRandPath() + createRandQuery());
   }
   
   // create the string to invalid value
   protected String makeInvalid(String pre, int invalidType) {
	   if(invalidType == 1) {
		   return ("!" + pre);
	   }
	   else if(invalidType == 2) {
		   return ("1" + pre);
	   }
	   else if(invalidType == 3) {
		   return ("." + pre);   
	   }
	   else {
		   return ("/" + pre);
	   }
   }
   
/*
   public void testIsValid() {
        testIsValid(testUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
        setUp();
//        int options =
//            UrlValidator.ALLOW_2_SLASHES
//                + UrlValidator.ALLOW_ALL_SCHEMES
//                + UrlValidator.NO_FRAGMENTS;
//    
//        testIsValid(testUrlPartsOptions, options);
   }
*/
   public void testIsValidScheme() {
      if (printStatus) {
         System.out.print("\n testIsValidScheme() ");
      }
      String[] schemes = {"http", "gopher"};
      //UrlValidator urlVal = new UrlValidator(schemes,false,false,false);
      UrlValidator urlVal = new UrlValidator(schemes, 0);
      for (int sIndex = 0; sIndex < testScheme.length; sIndex++) {
         ResultPair testPair = testScheme[sIndex];
         boolean result = urlVal.isValidScheme(testPair.item);
         assertEquals(testPair.item, testPair.valid, result);
         if (printStatus) {
            if (result == testPair.valid) {
               System.out.print('.');
            } else {
               System.out.print('X');
            }
         }
      }
      if (printStatus) {
         System.out.println();
      }

   }
   
   /**
    * Random Testing 
    */
   public void testRandomIsValid() {
       testRandomIsValid(randomTestUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
       setUp();
//       int options =
//           UrlValidator.ALLOW_2_SLASHES
//               + UrlValidator.ALLOW_ALL_SCHEMES
//               + UrlValidator.NO_FRAGMENTS;
//   
//       testIsValid(testUrlPartsOptions, options);
  }

   /*
    * Added at 3:49 pm
    */
   public void testTenTimes() {
	   
	   // All valid cases
	 for(int i = 0; i < 1000; i++) {
		 //System.err.println("in testTenTimes Line 179");
		   String randScheme = createRandScheme();
		   String randAuthority = createRandAuthority();
		   String randPort = createRandPort();
		   String randPath = createRandPath();
		   String randQuery = createRandQuery();
		   
		   ResultPair[] randTestScheme = {new ResultPair(randScheme, true)};
		   ResultPair[] randTestAuthority = {new ResultPair(randAuthority, true)};
		   ResultPair[] randTestPort = {new ResultPair(randPort, true)};
		   ResultPair[] randTestPath = {new ResultPair(randPath, true)};
		   ResultPair[] randTestQuery = {new ResultPair(randQuery, true)};
		   
		   Object[] randomTestUrlParts = {randTestScheme, randTestAuthority, randTestPort, randTestPath, randTestQuery};
		   
		   //int[] testPartsIndex = {0, 0, 0, 0, 0};
		   
	       testRandomIsValid(randomTestUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
	       setUp();
		}
	
	 // All Invalid cases
	 for(int i = 0; i < 100; i++) {
		 //System.err.println("in testTenTimes Line 179");
		 for(int j = 1; j < 5; j++) {
		
		   String randScheme = makeInvalid(createRandScheme(), j);
		   String randAuthority = makeInvalid(createRandAuthority(), j);
		   String randPort = makeInvalid(createRandPort(), j);
		   String randPath = makeInvalid(createRandPath(), j);
		   String randQuery = makeInvalid(createRandQuery(), j);
		   
		   ResultPair[] randTestScheme = {new ResultPair(randScheme, false)};
		   ResultPair[] randTestAuthority = {new ResultPair(randAuthority, false)};
		   ResultPair[] randTestPort = {new ResultPair(randPort, false)};
		   ResultPair[] randTestPath = {new ResultPair(randPath, false)};
		   ResultPair[] randTestQuery = {new ResultPair(randQuery, false)};
		   
		   Object[] randomTestUrlParts = {randTestScheme, randTestAuthority, randTestPort, randTestPath, randTestQuery};
		   
		   //int[] testPartsIndex = {0, 0, 0, 0, 0};
		   
	       testRandomIsValid(randomTestUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
	       setUp();
		 }
		}
		
   }
  
   
   
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
 /*  public void testIsValid(Object[] testObjects, long allowAllSchemes) {
	      UrlValidator urlVal = new UrlValidator(null, null, allowAllSchemes);
	      //UrlValidator urlVal = new UrlValidator(null, allowAllSchemes);
      assertTrue(urlVal.isValid("http://www.google.com"));
      assertTrue(urlVal.isValid("http://www.google.com/"));
      int statusPerLine = 60;
      int printed = 0;
      if (printIndex)  {
         statusPerLine = 6;
      }
      do {
          StringBuilder testBuffer = new StringBuilder();
         boolean expected = true;
         for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
            int index = testPartsIndex[testPartsIndexIndex];
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);
            expected &= part[index].valid;
         }
         String url = testBuffer.toString();
         boolean result = urlVal.isValid(url);
         if(result == true)
        	 System.out.println(url);
         assertEquals(url, expected, result);
         if (printStatus) {
            if (printIndex) {
               System.out.print(testPartsIndextoString());
            } else {
               if (result == expected) {
                  System.out.print('.');
               } else {
                  System.out.print('X');
               }
            }
            printed++;
            if (printed == statusPerLine) {
               System.out.println();
               printed = 0;
            }
         }
      } while (incrementTestPartsIndex(testPartsIndex, testObjects));
      if (printStatus) {
         System.out.println();
      }
   }
/*
   /**
    * Random Test
    */
   public void testRandomIsValid(Object[] testObjects, long allowAllSchemes) {
	      UrlValidator urlVal = new UrlValidator(null, null, allowAllSchemes);
	      //UrlValidator urlVal = new UrlValidator(null, allowAllSchemes);
	      //System.err.println("Got to Line 232");
   assertTrue(urlVal.isValid("http://www.google.com"));
   assertTrue(urlVal.isValid("http://www.google.com/"));
   int statusPerLine = 60;
   int printed = 0;
   if (printIndex)  {
      statusPerLine = 6;
   }
   do {
	   //System.err.println("Got to Line 241, within do while loop");
       StringBuilder testBuffer = new StringBuilder();
      boolean expected = true;
      for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
         int index = testPartsIndex[testPartsIndexIndex];
         ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
         testBuffer.append(part[index].item);
         expected &= part[index].valid;
      }
      String url = testBuffer.toString();
      boolean result = urlVal.isValid(url);
      if(result == true)
     	 System.out.println(url);
      System.out.println("Line 393: url " + url + "\nexpected " + expected + "\nresult " + result + "\n");
      assertEquals(url, expected, result);
      if (printStatus) {
         if (printIndex) {
            System.out.print(testPartsIndextoString());
         } else {
            if (result == expected) {
               System.out.print('.');
            } else {
               System.out.print('X');
            }
         }
         printed++;
         if (printed == statusPerLine) {
            System.out.println();
            printed = 0;
         }
      }
   } while (incrementTestPartsIndex(testPartsIndex, testObjects));
   if (printStatus) {
      System.out.println();
   }
}
   
   public void testValidator202() {
       String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes, UrlValidator.NO_FRAGMENTS);
       urlValidator.isValid("http://www.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.logoworks.comwww.log");
   }

   public void testValidator204() {
       String[] schemes = {"http","https"};
       UrlValidator urlValidator = new UrlValidator(schemes);
       assertTrue(urlValidator.isValid("http://tech.yahoo.com/rc/desktops/102;_ylt=Ao8yevQHlZ4On0O3ZJGXLEQFLZA5"));
   }

   static boolean incrementTestPartsIndex(int[] testPartsIndex, Object[] testParts) {
      boolean carry = true;  //add 1 to lowest order part.
      boolean maxIndex = true;
      for (int testPartsIndexIndex = testPartsIndex.length - 1; testPartsIndexIndex >= 0; --testPartsIndexIndex) {
         int index = testPartsIndex[testPartsIndexIndex];
         ResultPair[] part = (ResultPair[]) testParts[testPartsIndexIndex];
         if (carry) {
            if (index < part.length - 1) {
               index++;
               testPartsIndex[testPartsIndexIndex] = index;
               carry = false;
            } else {
               testPartsIndex[testPartsIndexIndex] = 0;
               carry = true;
            }
         }
         maxIndex &= (index == (part.length - 1));
      }


      return (!maxIndex);
   }

   private String testPartsIndextoString() {
       StringBuilder carryMsg = new StringBuilder("{");
      for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
         carryMsg.append(testPartsIndex[testPartsIndexIndex]);
         if (testPartsIndexIndex < testPartsIndex.length - 1) {
            carryMsg.append(',');
         } else {
            carryMsg.append('}');
         }
      }
      return carryMsg.toString();

   }

   public void testValidateUrl() {
      assertTrue(true);
   }

   /**
    * Only used to debug the unit tests.
    * @param argv
    */
/*   public static void main(String[] argv) {

	   UrlValidatorTest fct = new UrlValidatorTest("url test");
      fct.setUp();
  //    fct.testIsValid();
      fct.testIsValidScheme();
      
      //random testing
      for(int i = 0; i < 10; i++) {
    	  //System.err.println("for loop Line 342");
      fct.testRandomIsValid();
      }
   }
*/
   //-------------------- Test data for creating a composite URL
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   //ResultRandomPair[] testRandomScheme = {
   
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
                               new ResultPair("ftp://", true),
                               new ResultPair("h3t://", true),
                               new ResultPair("3ht://", false),
                               new ResultPair("http:/", false),
                               new ResultPair("http:", false),
                               new ResultPair("http/", false),
                               new ResultPair("://", false),
                               new ResultPair("", true)};

   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
                                  new ResultPair("go.com", true),
                                  new ResultPair("go.au", true),
                                  new ResultPair("0.0.0.0", true),
                                  new ResultPair("255.255.255.255", true),
                                  new ResultPair("256.256.256.256", false),
                                  new ResultPair("255.com", true),
                                  new ResultPair("1.2.3.4.5", false),
                                  new ResultPair("1.2.3.4.", false),
                                  new ResultPair("1.2.3", false),
                                  new ResultPair(".1.2.3.4", false),
                                  new ResultPair("go.a", false),
                                 new ResultPair("go.a1a", false),
                                  new ResultPair("go.1aa", false),
                                  new ResultPair("aaa.", false),
                                  new ResultPair(".aaa", false),
                                  new ResultPair("aaa", false),
                                  new ResultPair("", false)
   };
   ResultPair[] testUrlPort = {new ResultPair(":80", true),
                             new ResultPair(":65535", true),
                             new ResultPair(":0", true),
                             new ResultPair("", true),
                             new ResultPair(":-1", false),
                            new ResultPair(":65636",false),
                             new ResultPair(":65a", false)
   };
   ResultPair[] testPath = {new ResultPair("/test1", true),
                          new ResultPair("/t123", true),
                          new ResultPair("/$23", true),
                          new ResultPair("/..", false),
                          new ResultPair("/../", false),
                          new ResultPair("/test1/", true),
                          new ResultPair("", true),
                          new ResultPair("/test1/file", true),
                          new ResultPair("/..//file", false),
                          new ResultPair("/test1//file", false)
   };
   //Test allow2slash, noFragment
   ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                                    new ResultPair("/t123", true),
                                    new ResultPair("/$23", true),
                                    new ResultPair("/..", false),
                                    new ResultPair("/../", false),
                                    new ResultPair("/test1/", true),
                                    new ResultPair("/#", false),
                                    new ResultPair("", true),
                                    new ResultPair("/test1/file", true),
                                    new ResultPair("/t123/file", true),
                                    new ResultPair("/$23/file", true),
                                    new ResultPair("/../file", false),
                                    new ResultPair("/..//file", false),
                                    new ResultPair("/test1//file", true),
                                    new ResultPair("/#/file", false)
   };

   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
                              new ResultPair("?action=edit&mode=up", true),
                              new ResultPair("", true)
   };

   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
   
   // random part
   /*
   String randScheme = "http://";
   String randAuthority = "goo.com";
   String randPort = ":80";
   String randPath = "/test1";
   String randQuery = "?action=view";
   */
   String randScheme = createRandScheme();
   String randAuthority = createRandAuthority();
   String randPort = createRandPort();
   String randPath = createRandPath();
   String randQuery = createRandQuery();
   
   ResultPair[] randTestScheme = {new ResultPair(randScheme, true)};
   ResultPair[] randTestAuthority = {new ResultPair(randAuthority, true)};
   ResultPair[] randTestPort = {new ResultPair(randPort, true)};
   ResultPair[] randTestPath = {new ResultPair(randPath, true)};
   ResultPair[] randTestQuery = {new ResultPair(randQuery, true)};
   
   Object[] randomTestUrlParts = {randTestScheme, randTestAuthority, randTestPort, randTestPath, randTestQuery};
   
   int[] testPartsIndex = {0, 0, 0, 0, 0};

   //---------------- Test data for individual url parts ----------------
   ResultPair[] testScheme = {new ResultPair("http", true),
                            new ResultPair("ftp", false),
                            new ResultPair("httpd", false),
                            new ResultPair("telnet", false)};


}

