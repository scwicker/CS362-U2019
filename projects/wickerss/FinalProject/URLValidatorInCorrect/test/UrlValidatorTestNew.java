//package test;



//import static org.junit.Assert.*;

//import org.junit.After;
//import org.junit.Before;
//import org.junit.Test;
//import src.UrlValidator;
//import src.ResultPair;




import junit.framework.TestCase;

public class UrlValidatorTestNew extends TestCase
{

    public UrlValidatorTestNew(String testName)
    {
        super(testName);
    }


    /*
        @Before
        public void setUp(int index) throws Exception
        {


        }

        @After
        public void tearDown() throws Exception
        {


        }
    */

    public void testIsValid()
    {
        testIsValid(parts, UrlValidator.ALLOW_ALL_SCHEMES);
        //      setUp();
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

        int printed = 0;
        int statusPerLine = 6;

        int scheIndex = 0;
        int authIndex = 0;
        int portIndex = 0;
        int pathIndex = 0;
        int optiIndex = 0;
        int querIndex = 0;
        int allTested = 0;

        assertFalse(urlValid.isValid("ZAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA")); //test to see if IPV6 address is false

        boolean testCheck = urlValid.isValid("ZAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA:AAAA");

        if (testCheck == true)
        {
            System.out.print(testCheck);
        }

        do 
        {

            //whenever testIsValid is called, it's called with either the testObjects that includes the port options
            //or the testObjects that doesn't have the port options.


            if (testObjects.length == 5)
            {

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
                if (    scheme[scheIndex].valid == true &&
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
                    System.out.print("{" + scheIndex + ',' + authIndex + ',' + portIndex + ',' + pathIndex + ',' + optiIndex + ',' + querIndex + "} ");

                    printed++;
                    if (printed == statusPerLine)   //for legibility, can set statusPerLine above
                    {
                        System.out.println();
                        printed = 0;
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
    }


    //////////////////////////////////////////////////////////////Begin random test section //////////////
    public static int getRandomNumber(int min, int max)
    {

        int x = (int)(Math.random() * ((max - min) + 1)) + min;

        return x;

    }


    public void randomTestPermutations(Object[] testObjects, Long options)
    {

        System.out.println("This function calls isValid() with randomly combined segments of URLS.");

        UrlValidator urlValid = new UrlValidator(null, null, options);
        assertTrue(urlValid.isValid("http://www.google.com")); //test to see if working

        //need size of each segment  list for getRandomNumber() upper param
        int lowerLimit = 1;
        int upperLimit = 5;  // Change this to = class.randomlist.length or whatever

        int r = getRandomNumber(lowerLimit, 5); // then change 5 to upperLimit
        System.out.println(r);

        // then inside a for loop we'd need something like this maybe? For each of the segments..
        // testURL.append(scheme[getRandomNumber(lowerLimit, scheme.length].item);


    }

    ///////////////////////////////////////////   End random test section ////////////////////








    //list of each part, with a boolean value associated with it that tells if it is valid or not.
    // ResultPair contains and item ("ftp://") and a valid (true).

    ResultPair [] scheme =
    {
        new ResultPair("http://", true)

    };
    ResultPair [] authority =
    {
        new ResultPair("go.com:", false),
        new ResultPair("www.google.com", true),
        new ResultPair("", false)

    };
    ResultPair [] port =
    {
        new ResultPair("", true)


    };
    ResultPair [] path =
    {
        new ResultPair("", true),
        new ResultPair("/test1/", true)


    };
    ResultPair [] options =
    {
        //new ResultPair("", true)
        new ResultPair("/t123/file", true),
        new ResultPair("/$23/file", true),
        new ResultPair("/../file", false)


    };
    ResultPair [] query =
    {
        new ResultPair("", true)


    };


    Object[] parts = {scheme, authority, port, path, query};
    Object[] partsWithOptions = {scheme, authority, port, path, options, query};



}
