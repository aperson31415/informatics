# Word Wrap

**Time Limit**: 1.0s<br>
**Memory Limit**: ?<br>

**Input File:** `wrapin.txt`  
**Output File:** `wrapout.txt`  
**Time Limit:** 1 second

KDE, MacOS, Windows, it's all too much. These days everybody has a graphical user interface with a fancy word processor and proportional fonts. Plain text-based programs just aren't as trendy as they used to be.

You are determined to reverse this trend. One day you will make people understand the value of having a word processor that can run on a computer with under a megabyte of memory. Of course, you happen to be writing such a word processor at this very moment.

Your task here is to implement word wrapping in this word processor. That is, given a paragraph of text, you must arrange the words into lines so that the paragraph fits on your screen and is pleasing to the eye.

Since your word processor is a plain text-based program, you are using fixed width fonts. If your screen has width _w_ , this means that each line of your screen can fit precisely _w_ characters, including letters, digits, punctuation and spaces.

A _word_ is defined to be a consecutive sequence of letters, digits and/or punctuation surrounded by spaces on either side (although the first word of the paragraph need not be preceded by a space, and the last word of the paragraph need not be followed by a space). Thus the first word of the problem statement that you are reading now is "`KDE,`" including the comma, and the fourth word is "`it's`".

You must arrange the words into lines so that each line except for the last contains as many words as possible. Words within each line must be separated by at least one space, and the total length of each line (including spaces) must not exceed the screen width _w_.

Of course some lines may have total length less than _w_ , and so the question remains how to display such lines on the screen. You will be asked to use one of three styles of output: _left flushed_ , _right flushed_ and _justified_. These styles of output are explained below, and are illustrated in the sample data later in this question statement.

* In left flushed output, there must be precisely one space between any two adjacent words on a line. Furthermore, the first character of the first word of each line must be placed as far left as possible; i.e., in the first column of the display.
  * In right flushed output, there must again be precisely one space between any two adjacent words on a line. The last character of the last word of each line must be placed as far right as possible; i.e., in the _w_ th column of the display.
  * In justified output, the first character of the first word and the last character of the last word must be placed in the first and _w_ th columns of the display respectively. To allow for this, some words will need to be separated by more than one space.   
Spaces must be distributed as evenly as possible between the words on each line. If the spaces cannot be distributed evenly, more spaces must be given to the leftmost gaps. That is, the gaps between words on each line must remain equal or decrease in size from left to right, and the leftmost gap can be at most one space larger than the rightmost gap.   
As an exception, the final line of the paragraph must be left flushed as described earlier, with precisely one space between any two adjacent words.

## Input Format
Each input file will contain a single paragraph and a specification for how it is to be output. 
The first line of input will be of the form _s w_ , where _s_ is a single upper-case letter representing the output style and _w_ is the screen width. The letter _s_ will be either `L`, `R` or `J`, for left flushed, right flushed and justified output respectively. You are guaranteed that 3 <=  _w_ <= 70. 
Following this will be some number of lines containing the actual text of the paragraph. The final line of input will contain a single hash character (`#`). This hash is not considered to be part of the paragraph text. 
The paragraph text will contain between 1 and 1000 lines inclusive. Each of these lines will contain at least one word and be at most 80 characters long. None of these lines will contain any hash characters or tabs. If _m_ is the length of the longest word in the paragraph text, you are guaranteed that 2 _m_ +1 <=  _w_.

## Output Format
The output must contain the paragraph text laid out in the correct style as described above. Lines may contain leading spaces as required by the output style. Lines must not contain any trailing spaces. That is, there must be no spaces output after the final word on each line. The output must not contain any blank lines.


### Sample Input #1
```text
L 66

You have been hired     by a company

which needs to place   an information

  booth in a shopping mall.  The shopping mall also

contains four fake trees to add   ambiance   to a shopper's experience.

#
```

### Sample Output #1
```text
You have been hired by a company which needs to place an

information booth in a shopping mall. The shopping mall also

contains four fake trees to add ambiance to a shopper's

experience.
```


### Sample Input #2
```text
R 66

You have been hired     by a company

which needs to place   an information

  booth in a shopping mall.  The shopping mall also

contains four fake trees to add   ambiance   to a shopper's experience.

#
```

### Sample Output #2
```text
You have been hired by a company which needs to place an

      information booth in a shopping mall. The shopping mall also

           contains four fake trees to add ambiance to a shopper's

                                                       experience.
```


### Sample Input #3
```text
J 66

You have been hired     by a company

which needs to place   an information

  booth in a shopping mall.  The shopping mall also

contains four fake trees to add   ambiance   to a shopper's experience.

#
```

### Sample Output #3
```text
You  have  been  hired  by  a  company  which  needs  to  place an

information  booth  in  a  shopping  mall.  The shopping mall also

contains   four   fake  trees  to  add  ambiance  to  a  shopper's

experience.
```



<br><br>

_Please note that this is an unnofficial document generated by aperson31415, who is in no way affiliated with the AMT. If someone from the AMT is unhappy with this, please contact aperson31415 on github. Some features of this problem might be missing, such as explanations to the sample inputs, or subtasks._

_This document should not be redistributed for payment, and please give attribution to the AMT for this problem (honestly, just look at what they say), and where it appeared (find out on aperson31415's 'informatics' repository). However, feel free to use this for personal study._