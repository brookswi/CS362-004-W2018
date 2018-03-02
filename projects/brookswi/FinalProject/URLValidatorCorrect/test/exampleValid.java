public void testIsValid(Object[] testObjects, long allowAllSchemes) {
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
			// testPartsIndexIndex = 0
            int index = testPartsIndex[testPartsIndexIndex]; // index = 0
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);  // part[index].item = "http://"
            expected &= part[index].valid;        // expected = true && part[index].valid = true so expected = true
         }
		 for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
			// testPartsIndexIndex = 1
            int index = testPartsIndex[testPartsIndexIndex]; // index = 0
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);  // part[index].item = "www.google.com"
            expected &= part[index].valid;        // expected = true && part[index].valid = true so expected = true
         }
		 for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
			// testPartsIndexIndex = 2
            int index = testPartsIndex[testPartsIndexIndex]; // index = 0
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);  // part[index].item = ":80"
            expected &= part[index].valid;        // expected = true && part[index].valid = true so expected = true
         }
		 for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
			// testPartsIndexIndex = 3
            int index = testPartsIndex[testPartsIndexIndex]; // index = 1
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);  // part[index].item = "/.."
            expected &= part[index].valid;        // expected = true && part[index].valid = false so expected = false
         }
		 for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
			// testPartsIndexIndex = 4
            int index = testPartsIndex[testPartsIndexIndex]; // index = 0
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);  // part[index].item = "?action=view"
            expected &= part[index].valid;        // expected = false && part[index].valid = true so expected = false
         }
         // Call UrlValidator method isVal() which checks url against a library of url patterns
		 String url = testBuffer.toString();  // url = "http://www.google.com:80/test1?action=view"
         boolean result = urlVal.isValid(url); // result should equal true
         if(result == true)
        	 System.out.println(url);
		 // Test that result from isValid() equal to expected result
         assertEquals(url, expected, result); // expected and result should both equal false
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