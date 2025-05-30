#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "Dictionary.hpp"

std::vector<std::string> getWords(std::string text)
{
    std::vector<std::string> wordList;
    size_t lastSpacePos = 0;
    auto nextSpacePos = std::min(text.find(" "), text.find("/n"));
    std::string word = "";
    while (nextSpacePos != std::string::npos)
    {
        word = text.substr(lastSpacePos, nextSpacePos - lastSpacePos);
        lastSpacePos = nextSpacePos + 1;
        nextSpacePos = std::min(text.find(" ", lastSpacePos), text.find("/n", lastSpacePos));

        word.erase(std::remove_if(word.begin(), word.end(), [](char c) { return !(c == '\'' || c == '-' || std::isalpha(c)); }), word.end());
        if (word != "" && word.front() == '\'')
            word.erase(0);
        if (word != "" && word.back() == '\'')
            word.erase(word.size() - 1);
        if (word != "")
            wordList.emplace_back(word);
    }
    return wordList;
}

int main()
{
    std::string text = "If you happen to have read another book about \
		Christopher Robin, you may remember that he once had \
		a swan (or the swan had Christopher Robin, I don't \
		know which), and that he used to call this swan Pooh. \
		That was a long time ago, and when we said good-bye, \
		we took the name with us, as we didn't think the swan \
		would want it any more. Well, when Edward Bear said \
		that he would like an exciting name all to himself, \
		Christopher Robin said at once, without stopping to \
		think, that he was Winnie-the-Pooh. And he was. So, as \
		I have explained the Pooh part, I will now explain the \
		rest of it. \
		\n \
		You can't be in London for long without going to the \
		Zoo. There are some people who begin the Zoo at the \
		beginning, called WAYIN, and walk as quickly as they \
		can past every cage until they get to the one called \
		WAYOUT, but the nicest people go straight to the \
		animal they love the most, and stay there. So when \
		Christopher Robin goes to the Zoo, he goes to where the \
		Polar Bears are, and he whispers something to the third \
		keeper from the left, and doors are unlocked, and we \
		wander through dark passages and up steep stairs, until \
		at last we come to the special cage, and the cage is \
		opened, and out trots something brown and furry, and \
		with a happy cry of 'Oh, Bear!' Christopher Robin rushes \
		into its arms. Now this bears name is Winnie, which \
		shows what a good name for bears it is, but the funny \
		thing is that we can't remember whether Winnie is \
		called after Pooh, or Pooh after Winnie. We did know \
		once, but we have forgotten... \
		\n \
		I had written as far as this when Piglet looked up and \
		said in his squeaky voice, 'What about Me?' 'My dear \
		Piglet,' I said, 'the whole book is about you.' 'So it is about \
		Pooh,' he squeaked. You see what it is. He is jealous \
		because he thinks Pooh is having a Grand Introduction all \
		to himself. Pooh is the favourite, of course, there's no \
		denying it, but Piglet comes in for a good many things \
		which Pooh misses; because you can't take Pooh to school \
		without everybody knowing it, but Piglet is so small that \
		he slips into a pocket, where it is very comforting to feel \
		him when you are not quite sure whether twice seven is \
		twelve or twenty-two. Sometimes he slips out and has a \
		good look in the ink-pot, and in this way he has got more \
		education than Pooh, but Pooh doesn't mind. Some have \
		brains, and some haven't, he says, and there it is. \
		\n \
		And now, all the others are saying, 'What about Us?'. \
		So perhaps the best thing to do is to stop writing \
		Introductions and get on with the book. ";

    auto words = getWords(text);
    auto chosenWords = { "he", "He", "Pooh", "the", "The", "I" };
    std::cout << "------------------PART 0.1------------------" << std::endl;
    std::cout << "Test using STL unordered_map" << std::endl;
    std::unordered_map<std::string, int> wordCountSTL;
    for (auto& word : words)
    {
        wordCountSTL[word]++;
    }
    std::cout << "Chosen words for the check:" << std::endl;
    for (auto& word : chosenWords)
    {
        std::cout << word << ": " << wordCountSTL[word] << std::endl;
    }
    std::cout << "------------------PART 1, 2 and 3------------------" << std::endl;
    Dictionary<std::string, int> wordCountTemplated;
    for (auto& word : words)
    {
    	wordCountTemplated[word]++;
    }
    for (auto& word : chosenWords)
    {
    	std::cout << word << ": " << wordCountTemplated[word] << std::endl;
    }
    std::cout << "Dictionary for mapping numbers and number english names:" << std::endl;
    Dictionary<int, std::string> numbersEnglishNames;
    numbersEnglishNames.insert(1, "one");
    numbersEnglishNames.insert(2, "two");
    numbersEnglishNames.insert(100, "hundred");
    std::cout << numbersEnglishNames << std::endl;
    std::cout << "------------------PART 4------------------" << std::endl;
    std::cout << numbersEnglishNames << std::endl;

    std::cout << "------------------PART 5------------------" << std::endl;
    Dictionary<int, std::string> numbersEnglishNames2;
    numbersEnglishNames2.insert(3, "three");
    numbersEnglishNames2.insert(4, "four");
    numbersEnglishNames2.insert(100, "onehundred");

    auto intersect = numbersEnglishNames.intersect(numbersEnglishNames2);
    std::cout << intersect << std::endl;

    std::cout << "------------------PART 6------------------" << std::endl;
    auto sum = numbersEnglishNames + numbersEnglishNames2;
    std::cout << sum << std::endl;
    std::cout << "------------------PART 7------------------" << std::endl;
    try {
    	numbersEnglishNames.remove(3);
    }
    catch (std::exception& e) {
    	std::cout << e.what() << std::endl;
    }
    auto intersect2 = numbersEnglishNames.intersect(numbersEnglishNames2);
    std::cout << intersect2 << std::endl;

    return 0;
}