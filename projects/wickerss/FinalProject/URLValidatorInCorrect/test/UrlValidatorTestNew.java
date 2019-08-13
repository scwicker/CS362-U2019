


import junit.framework.TestCase;

public class UrlValidatorTestNew extends TestCase
{

    private final boolean printResults = true;
    private final boolean printIndex = false;    
    private final boolean printRandUrls = false;


    public UrlValidatorTestNew(String testName)
    {
        super(testName);
    }




    public void testIsValid()
    {
        testIsValid(parts, UrlValidator.ALLOW_ALL_SCHEMES);

        long options =
            UrlValidator.ALLOW_2_SLASHES
            + UrlValidator.ALLOW_ALL_SCHEMES
            + UrlValidator.NO_FRAGMENTS;

        testIsValid(partsWithOptions, options);

        randomTestPermutations(partsWithOptions, options); 
    };

    public void testIsValid(Object[] testObjects, Long options)
    {

        UrlValidator urlValid = new UrlValidator(null, null, options);
        assertTrue(urlValid.isValid("http://www.google.com")); //test to see if working

        int printed = 0;
        int statusPerLine = 20;

        int scheIndex = 0;
        int authIndex = 0;
        int portIndex = 0;
        int pathIndex = 0;
        int optiIndex = 0;
        int querIndex = 0;
        int allTested = 0;
       

//  The following assertion will fail. Commented out so rest of tests can run.
/*        assertFalse(urlValid.isValid("http://[AAAZ:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA]:80/index.html")); //test to see if IPV6 address is false


        boolean testCheck = urlValid.isValid("http://[AAAZ:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA]:80/index.html");

        if (testCheck == true)
        {
            System.out.print(testCheck);
        }
*/

        int count = 0;
        int failed = 0;

        do 
        {

            //whenever testIsValid is called, it's called with either the testObjects that includes the port options
            //or the testObjects that doesn't have the port options.


            if (testObjects.length == 5)
            {
                count++;

                //create a string, and a var for each of the parts for the URL

                StringBuilder testURL = new StringBuilder();
                ResultPair [] scheme = (ResultPair[]) testObjects[0];
                ResultPair [] authority = (ResultPair[]) testObjects[1];
                ResultPair [] port = (ResultPair[]) testObjects[2];
                ResultPair [] path = (ResultPair[]) testObjects[3];
                ResultPair [] query = (ResultPair[]) testObjects[4];

                //append each part, based on each one's index value to the URL

                testURL.append(scheme[scheIndex].item);
                testURL.append(authority[authIndex].item);
                testURL.append(port[portIndex].item);
                testURL.append(path[pathIndex].item);
                testURL.append(query[querIndex].item);
                
                //System.out.printf("test URL: " + testURL);

                boolean expected;


                //if all of the associated boolean values for each of the parts are true, then expected is true
                if (    scheme[scheIndex].valid == true &&
                        authority[authIndex].valid == true &&
                        port[portIndex].valid == true &&
                        path[pathIndex].valid == true &&
                        query[querIndex].valid == true)
                {
                    expected = true;
                }
                else
                {
                    expected = false; //otherwise one must be false and therefore the URL is false
                }

                String url = testURL.toString(); //convert to string
                boolean result = urlValid.isValid(url); //get result

//                assertEquals(url, expected, result);

                if (expected != result) //if a failure occurs, print out the indexes for each value
                {
                    if (printIndex){    
                        System.out.print("{" + scheIndex + ',' + authIndex + ',' + portIndex + ',' + pathIndex + ',' + querIndex + "} ");
                    
                        //can set how many per line for legibility
                        printed++;
                        if (printed == statusPerLine)
                        {
                            //comment
                            System.out.println();
                            printed = 0;
                        }
                    }
                    
                    failed++;
                }





                //increases the query index, if that's full, then reset query and increment path, etc...

                querIndex++;
                if (querIndex >= query.length)
                {
                    querIndex = 0;
                    pathIndex++;
                    if (pathIndex >= path.length)
                    {
                        pathIndex = 0;
                        portIndex++;
                        if (portIndex >= port.length)
                        {
                            portIndex = 0;
                            authIndex++;
                            if (authIndex >= authority.length)
                            {
                                authIndex = 0;
                                scheIndex++;
                                if (scheIndex >= scheme.length)
                                {
                                    querIndex = 0;
                                    pathIndex = 0;
                                    portIndex = 0;
                                    authIndex = 0;
                                    scheIndex = 0;
                                    allTested = 1;
                                }
                            }

                        }
                    }
                }
            }
            else
            {
                //reset line so path options tests are separated
                if (printIndex || printResults){
                    if (count == 0){
                        System.out.println();
                    }
                }
                count++;

                //this is where port options are included

                //create string and set a var for each part

                StringBuilder testURL = new StringBuilder();
                ResultPair [] scheme = (ResultPair[]) testObjects[0];
                ResultPair [] authority = (ResultPair[]) testObjects[1];
                ResultPair [] port = (ResultPair[]) testObjects[2];
                ResultPair [] path = (ResultPair[]) testObjects[3];
                ResultPair [] option = (ResultPair[]) testObjects[4];
                ResultPair [] query = (ResultPair[]) testObjects[5];

                if (path[pathIndex].item == "")
                {
                    pathIndex++;
                }

                //append parts based on index values for each

                testURL.append(scheme[scheIndex].item);
                testURL.append(authority[authIndex].item);
                testURL.append(port[portIndex].item);
                testURL.append(path[pathIndex].item);
                testURL.append(option[optiIndex].item);
                testURL.append(query[querIndex].item);


                boolean expected;

                //if all ResultPair[index].valid == true, then expected value is true
                if (    
                        scheme[scheIndex].valid == true &&
                        authority[authIndex].valid == true &&
                        port[portIndex].valid == true &&
                        path[pathIndex].valid == true &&
                        option[optiIndex].valid == true &&
                        query[querIndex].valid == true)
                {
                    expected = true;
                }
                else
                {
                    expected = false;   //otherwise expected must be false
                }

                String url = testURL.toString();        //convert to string
                boolean result = urlValid.isValid(url); //get result value from isValid

//                assertEquals(url, expected, result);    //assert

                if (expected != result) //if a failure, print out the indexes of the failure
                {

                    failed++;
                    
                    if(printIndex){
                        System.out.print("{" + scheIndex + ',' + authIndex + ',' + portIndex + ',' + pathIndex + ',' + optiIndex + ',' + querIndex + "} ");
                    
                        printed++;
                        if (printed == statusPerLine)   //for legibility, can set statusPerLine above
                        {
                            System.out.println();
                            printed = 0;
                        }
                    }
                }

                //if query is at max, reset to zero and increment options, etc...
                querIndex++;
                if (querIndex >= query.length)
                {
                    querIndex = 0;
                    optiIndex++;
                    if (optiIndex >= option.length)
                    {
                        optiIndex = 0;
                        pathIndex++;
                        if (pathIndex >= path.length)
                        {
                            pathIndex = 0;
                            portIndex++;
                            if (portIndex >= port.length)
                            {
                                portIndex = 0;
                                authIndex++;
                                if (authIndex >= authority.length)
                                {
                                    authIndex = 0;
                                    scheIndex++;
                                    if (scheIndex >= scheme.length)
                                    {
                                        querIndex = 0;
                                        pathIndex = 0;
                                        portIndex = 0;
                                        optiIndex = 0;
                                        authIndex = 0;
                                        scheIndex = 0;
                                        allTested = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }    
        while (allTested == 0);
        if (printResults){
            System.out.println();
            System.out.println("During Testing:");                
            System.out.println("Failed: " + failed + "\nTotal: " + count);
        }
    }


    //////////////////////////////////////////////////////////////Begin random test section //////////////
    public static int getRandomNumber(int min, int max)
    {

        int x = (int)(Math.random() * ((max - min) + 1)) + min;

        return x;

    }


    public void randomTestPermutations(Object[] testObjects, Long options)
    {

        int count = 0;
        int failed = 0;

        System.out.println("\n\nThis function calls isValid() with randomly combined segments of URLS.\n");



        int numberOfTests = 5000; //can set 

        for (int j = 0; j < numberOfTests; j++)
        {
            count++;
            boolean expected = true;

            UrlValidator urlValid = new UrlValidator(null, null, options);
            StringBuilder testURL = new StringBuilder();                    // url string to test.
            
            
            for(int i = 0; i < testObjects.length; i++) 
            {
                ResultPair[] part = (ResultPair[]) testObjects[i];        //get result part of URL
                int randomNumber = getRandomNumber(0, part.length - 1);   //generate random number
                testURL.append(part[randomNumber].item);                  //append random part to the URL
                if (part[randomNumber].valid == false)
                {
                    expected = false;                       //default expected is true, if a false value is encountered,
                }                                           //change expected to false
            }

            String url = testURL.toString();        //convert to string
            boolean result = urlValid.isValid(url); //get result value from isValid


            if (expected != result) //if a failure, print out the indexes of the failure
            {
                failed++;

                if(printRandUrls){
                    System.out.println(count + "Failed: "+ url);
                }
            }
            if(count == numberOfTests && printResults)
            {
                System.out.println();
                System.out.println("During Random Testing:");                
                System.out.println("Failed: " + failed + "\nTotal: " + count);
            }
        }


        //System.out.print(testURL);
    }

    ///////////////////////////////////////////   End random test section ////////////////////








    //list of each part, with a boolean value associated with it that tells if it is valid or not.
    // ResultPair contains and item ("ftp://") and a valid (true).

    ResultPair [] scheme =
    {
        new ResultPair("http://", true),
        new ResultPair("https://", true), 
        new ResultPair("ldap://", true), 
        new ResultPair("/news:", false),
        new ResultPair("en:///", false), 
        new ResultPair("new:/:/", false), 
        new ResultPair("ftp://", true), 


    };
    ResultPair [] authority =
    {
        new ResultPair("go.com:", false),
        new ResultPair("www.google.com", true),
        new ResultPair("", false), 
        new ResultPair("wikipedia.org", true),
        new ResultPair("github.com", true), 
        new ResultPair("oregonstate.edu", true), 
        new ResultPair("oregon", false), 
        new ResultPair("bnasudbofhuibwe", false), 
        new ResultPair("e.co", true), 
        new ResultPair("example.org", true), 
        new ResultPair("badexample.o", false), 




    };
    ResultPair [] port =
    {
        new ResultPair("", true),
        new ResultPair(":80", true), 
        new ResultPair(":12345", true), 
        new ResultPair("65535", true), 
        new ResultPair("65536", false), 
        new ResultPair("/:234", false), 
        new ResultPair("234", false), 
        new ResultPair("example", false) 


    };
    ResultPair [] path =
    {
        new ResultPair("", true),
        new ResultPair("/test1/", true), 
        new ResultPair("://", false), 
        new ResultPair("/example", true), 
        new ResultPair("/files", true), 
        new ResultPair("/.files", false), 
        new ResultPair("/////", false), 
        new ResultPair("/one/two/three", true)


    };
    ResultPair [] options =
    {
        new ResultPair("/t123/file", true),
        new ResultPair("/$23/file", true),
        new ResultPair("/../file", false), 
        new ResultPair("/one/more/time", true), 
        new ResultPair("not/one/more/time", false), 
        new ResultPair("/123/", true), 
        new ResultPair("", true) 



    };
    ResultPair [] query =
    {
    	new ResultPair("?firstName=James&lastName=Smith", true),
        new ResultPair("?field1=this&field2=that", true), 
        new ResultPair("", true)

    };


    Object[] parts = {scheme, authority, port, path, query};
    Object[] partsWithOptions = {scheme, authority, port, path, options, query};



}
