

import java.util.Scanner;
import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {
	
	String[] scheme = {"http","https","imap","ftp","ssh"};
	
	String[] authority = {"en:wikipedia.org", "en.wikipedia.org", "wikipedia.org", "", null, "pmtpa.wikimedia.org",
			"_.wikipedia.org", "0.wikipedia.org", "-en.wikipedia.org", " ",
			"en..wikipedia.org", "192.0.2.235", "0.0.0.0", "192.0.2.256",
			"255.255.255.255", "255.256.255.254", "2555.255.255.2",
			"en.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmno.org",
			"en.abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnop.org",
			"en/.wikipedia.org", "0wikipedia.org", "-wikipedia.org", "en.wiki pedia.org", 
			"2001:db8:a0b:12f0::1", "2001:db8:0:0:0:0:2:1", "2001:db8::2:1"};
	
	String[] path = {"/test1", "/t123", "/$23", "/..", "/../", "/test1/", ""};

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
//   public void testManualTest()
//   {
//	   String[] schemes = {"http","https","imap","ftp","ssh"};
//	   String	urlStr;
//	   
//	   Scanner  userIn = new Scanner(System.in); 	   
//	   UrlValidator urlValidator = new UrlValidator(schemes);
//	   
//	   while (true) {
//		   urlStr = userIn.nextLine();
//		   
//		   if (urlStr == "")
//			   break;
//		   
//		   if (urlValidator.isValid(urlStr)) {
//			   System.out.println("url is valid");
//		   } else {
//			   System.out.println("url is invalid");
//		   }   
//	   }
//	   System.out.println("Exiting Test");
//	   userIn.close(); 
//   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
//   public void testYourSecondPartition(){
//
//	   String[] schemes = {"http","https","imap","ftp","ssh"};
//
//	   UrlValidator urlValidator = new UrlValidator(schemes);
//
//	   
//	   for(int j = 1; j < scheme.length; j++) {
//		   for(int i = 0; i < authority.length; i++) {
//			   String testURL = scheme[j] + "://" + authority[i];
//			   if (urlValidator.isValid(testURL)) {
//				   System.out.printf("the url %s with authority %s is valid\n", testURL, authority[i]);
//			   } else {
//				   System.out.printf("the url %s with authority %s is invalid\n", testURL, authority[i]);
//			   }
//		   }
//	   }
//
//
//   }

   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   UrlValidator urlValidator = new UrlValidator(scheme);

	   for(int i = 0; i<scheme.length; i++) {
		   for(int j=0; j<authority.length; j++) {
			   for(int k=0; k<path.length; k++) {
				   String testURL = scheme[i] + "://"+ authority[j] + path[k];
				   if (urlValidator.isValid(testURL)) {
					   System.out.printf("the url %s is valid\n", testURL);
				   } else {
					   System.out.printf("the url %s is invalid\n", testURL);
				   }
				   
			   }
		   }
	   }

   }
	
   /*******************************************************************
   ** Random String Creating Helper Functions
   ** 	returns specifically selected type of string as needed
   **	createRandAlpha(int length): use for scheme, authority...
   **	createRandAlphaNum(int length, boolean withSlash): if withSlash is passed as true
   **		it returns with slash in the string.  Ex: bb223/br
   **	createRandNum(int min, int max): use for creating random port #
   ********************************************************************/
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
    /*******************************************************************
   ** End of Random String Creating Helper Functions
   ********************************************************************/  


}
