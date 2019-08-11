//package test;



//import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
//import src.UrlValidator;
//import src.ResultPair;

import junit.framework.TestCase;




public class UrlValidatorTestNew extends TestCase {

	@Before
	public void setUp(int index) throws Exception {

		
    }

	@After
	public void tearDown() throws Exception {
				
		
	}

	@Test
	public void testIsValid()
	{
		testIsValid(parts, UrlValidator.ALLOW_ALL_SCHEMES);
//		setUp();
		long options =
          UrlValidator.ALLOW_2_SLASHES
          + UrlValidator.ALLOW_ALL_SCHEMES
          + UrlValidator.NO_FRAGMENTS;

      testIsValid(partsWithOptions, options);
	};
	
	public void testIsValid(Object[] testObjects, Long options)
	{

		UrlValidator urlValid = new UrlValidator(null, null, options);
		assertTrue(urlValid.isValid("http://www.google.com")); //test to see if working
		
		int scheIndex = 0;
		int authIndex = 0;
		int portIndex = 0;
		int pathIndex = 0;
		int optiIndex = 0;
		int querIndex = 0;
		int allTested = 0;


		while (allTested == 0)
		{
			if (testObjects.length == 5)
			{
				StringBuilder testURL = new StringBuilder();
				ResultPair [] scheme = (ResultPair[]) testObjects[0];
				ResultPair [] authority = (ResultPair[]) testObjects[1];
				ResultPair [] port = (ResultPair[]) testObjects[2];
				ResultPair [] path = (ResultPair[]) testObjects[3];
				ResultPair [] query = (ResultPair[]) testObjects[4];
				
				testURL.append(scheme[scheIndex].item);
				testURL.append(authority[authIndex].item);
				testURL.append(port[portIndex].item);
				testURL.append(path[pathIndex].item);
				testURL.append(query[querIndex].item);
				
				boolean expected;

				if (	scheme[scheIndex].valid == true && 
						authority[authIndex].valid == true && 
						port[portIndex].valid == true && 
						path[pathIndex].valid == true && 
						query[querIndex].valid == true)
				{
					expected = true;
				} else {
					expected = false;
				}

				String url = testURL.toString();
				boolean result = urlValid.isValid(url);

				assertEquals(expected, result);

				if (expected != result)
				{
					System.out.print("\n{" + scheIndex + ',' + authIndex + ',' + portIndex + ',' + pathIndex + ',' + querIndex + '}');
				}


				querIndex++;

				if (querIndex >= query.length){
					querIndex = 0;
					pathIndex++;
					if (pathIndex >= path.length){
						pathIndex = 0;
						portIndex++;
						if (portIndex >= port.length){
							portIndex = 0;
							authIndex++;
							if (authIndex >= authority.length){
								authIndex = 0;
								scheIndex++;
								if (scheIndex >= scheme.length){
									allTested = 1;
								}
							}

						}
					}
				}
			} else {

				StringBuilder testURL = new StringBuilder();
				ResultPair [] scheme = (ResultPair[]) testObjects[0];
				ResultPair [] authority = (ResultPair[]) testObjects[1];
				ResultPair [] port = (ResultPair[]) testObjects[2];
				ResultPair [] path = (ResultPair[]) testObjects[3];
				ResultPair [] option = (ResultPair[]) testObjects[4];
				ResultPair [] query = (ResultPair[]) testObjects[5];

				testURL.append(scheme[scheIndex].item);
				testURL.append(authority[authIndex].item);
				testURL.append(port[portIndex].item);
				testURL.append(path[pathIndex].item);
				testURL.append(option[optiIndex].item);
				testURL.append(query[querIndex].item);
				

				boolean expected;

				if (	scheme[scheIndex].valid == true && 
						authority[authIndex].valid == true && 
						port[portIndex].valid == true && 
						path[pathIndex].valid == true && 
						option[optiIndex].valid == true &&
						query[querIndex].valid == true)
				{
					expected = true;
				} else {
					expected = false;
				}

				String url = testURL.toString();
				boolean result = urlValid.isValid(url);

				assertEquals(expected, result);

				if (expected != result)
				{
					System.out.print("\n{" + scheIndex + ',' + authIndex + ',' + portIndex + ',' + pathIndex + ',' + optiIndex + ',' + querIndex + '}');
				}


				querIndex++;

				if (querIndex >= query.length){
					querIndex = 0;
					optiIndex++;
					if (optiIndex >= option.length){
						optiIndex = 0;
						pathIndex++;
						if (pathIndex >= path.length){
							pathIndex = 0;
							portIndex++;
							if (portIndex >= port.length){
								portIndex = 0;
								authIndex++;
								if (authIndex >= authority.length){
									authIndex = 0;
									scheIndex++;
									if (scheIndex >= scheme.length){
										allTested = 1;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	

//////////////////////////////////////////////////////////////Begin random test section //////////////
public static int getRandomNumber(int min, int max){

int x = (int)(Math.random()*((max-min)+1))+min;

return x;

}   


public void randomTestPermutations(Object[] testObjects, Long options) {

	System.out.println("This function calls isValid() with randomly combined segments of URLS.");
	
	UrlValidator urlValid = new UrlValidator(null, null, options);
	assertTrue(urlValid.isValid("http://www.google.com")); //test to see if working
	
	//need size of each segment  list for getRandomNumber() upper param
	int lowerLimit = 1;
	int upperLimit = 5;  // Change this to = class.randomlist.length or whatever
	
	int r = getRandomNumber(lowerLimit,5);  // then change 5 to upperLimit
	System.out.println(r);
	
	// then inside a for loop we'd need something like this maybe? For each of the segments..
	// testURL.append(scheme[getRandomNumber(lowerLimit, scheme.length].item);
	

}

///////////////////////////////////////////   End random test section ////////////////////

	

	
	
	ResultPair [] scheme = { 
			new ResultPair("http://", true),
//			new ResultPair("", ),
//			new ResultPair("", );
	};
	ResultPair [] authority = {
			new ResultPair("", false),
//			new ResultPair("", );
	};
	ResultPair [] port = {
			new ResultPair("", false),
//			new ResultPair("", );
	};
	ResultPair [] path = {
			new ResultPair("", true),
//			new ResultPair("", );
	};
	ResultPair [] options = {
			new ResultPair("", true),
//			new ResultPair("", );
	};
	ResultPair [] query = {
			new ResultPair("", true),
//			new ResultPair("", );
	}; 
	
		
    Object[] parts = {scheme, authority, port, path, query};
    Object[] partsWithOptions = {scheme, authority, port, options, query};
    int[] testPartsIndex = {0, 0, 0, 0, 0};
	
	

	

}
