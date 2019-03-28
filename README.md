#FINAL PROJECT - ALYSON JIMENEZ
included: Dictionary.cpp, Dictionary.h, main.cpp
downloads: dictionary.txt (which needs to be used in order for code to work)

This project definitely tested my c++ skills, organization and overall my patience when it comes to code. I knew that creating a dictionary would be difficult but the more I worked on it, I realized there is a lot to consider when just writing a physical dictionary. Trying to keep in mind the end goal and exactly what was I working with was important in completing this code. 

The Project Goal
The goal was to create a dictionary that can be accessed at any time. In addition, the dictionary will include a user-created list of words. The user would be able to add an entry that includes word, part of speech, and definiton. The user will be able to edit any preexisting entry in the dictionary. The user will be able to search for any preexisting entry in the dictionary. 

My Main Issues
As with my previous projects, when trying to commit, the entire project would disappear so I used a copy of the project as a tester so I would not have to repeat the project over. I was having issues with using the fstream library and how it relates to the code. I tried multiple ways to try to let the user use the dictionary such as making it a map, list, and array. But I was more familiar with vectors so I used it instead. It took me a while to understand why I needed to overload the comparision operator as I was testing out using the lower_bound function. I figured that lower_bound would be more suitable as to consider how the vector works when entering a new entry. Another huge issue I had was when I would run the code and enter a command, it would revert back to the menu. I later learned that getline catches all the entry all the way to the new line but even then I did not know a solution. I consulted a tutor for only this part because I was not able to find a solution online. Lastly, another issue I had was making sure, in loading the Dictionary to the vector, that everything was accounted for. The text file in the downloads page corresponds to the code as it is case senstitive. That block of code took me the longest to figure out but with patience, I managed to figure it out.  

Concepts Used (LINKS)
Fstream library: http://www.cplusplus.com/reference/fstream/fstream/?kw=fstream
Vectors:http://www.cplusplus.com/reference/vector/vector/?kw=vector
Binary Search: http://www.cplusplus.com/reference/algorithm/binary_search/
Getline: http://www.cplusplus.com/reference/string/string/getline/?kw=getline
Lower Bound: http://www.cplusplus.com/reference/algorithm/lower_bound/?kw=lower_bound
Iterators: http://www.cplusplus.com/reference/iterator/iterator/?kw=iterator
Forward Iterators: http://www.cplusplus.com/reference/iterator/ForwardIterator/
Numeric Limits: http://www.cplusplus.com/reference/limits/numeric_limits/?kw=numeric_limits
String::npos:http://www.cplusplus.com/reference/string/string/npos/
size_t: http://www.cplusplus.com/reference/cstddef/size_t/?kw=size_t

What I Learned
I learned a lot from this project as I had to think outside the box. I learned more about iterators and their types, I used forward iterators in my project but I had to make it both regular and constant. I learned more about fstream library and exactly what is needed for files to work with the code. It was very interesting to learn about strings and how important it was to acknowledge what is in the string. Making sure that everything was organized and that I had the output in mind was something that I figured out I needed to do very early on. Lastly, I learned about binary search and how efficient it is. It does seem a lot easier than searching through every entry in the vector. Reading online about what binary search does and what it returns (which is something that always needs to be considered) and also how it effects the speed is something that I will consider in future projects. 

Going Forward 
Overall, this project was a challenge, but it was a good one. I unfortunately was unable to get the phonetics part of the dictionary as I was hoping as I did spend a whole week on it but hopefully I can expand on this project with that idea. I used to be afraid of using iterators because there's a lot to consider but after this project, I realized that iterators make life and code so much easier. Using my references and making sure that everything was returning certain types made using iterators less scary. In addition, I do want to work more with fstream and incorporate that into my study of linguistics. I did this project originally to help me with my linguistics study but hopefully I will able to use this dictionary for various languages. It was most rewarding to be able to complete this code and be able to tell myself that I have the skills and knowledge to do more difficult projects and not be afraid to explore different concepts. 