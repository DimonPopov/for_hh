#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>

int countOfPatterns = 0;



class Vertex
{
public:
  Vertex(char vertex_ = '?', Vertex *parent_ = nullptr) : vertex(vertex_), parent(parent_) {}
  char vertex = '?';
  bool isTerminal = false;
  Vertex *parent = nullptr;
  Vertex *suffixLink = nullptr;
  Vertex *terminalLink = nullptr;
  std::vector<int> number;
  int stringLen = 0;
  std::map<char, Vertex *> child;
};



std::map<std::string, std::vector<int>> getPatterns(std::string pattern, char joker)
{
  countOfPatterns = 0;
  std::map<std::string, std::vector<int>> indices;
  int left = 0, right = 0;
  char symbol;
  for (size_t i = 0; i < pattern.size(); ++i)
  {
    symbol = pattern[i];

    if (symbol == joker && left != right)
    {
      std::string substring = pattern.substr(left, right - left);
      if (indices.find(substring) == indices.end())
        indices[substring] = {left};
      else
        indices[substring].push_back(left);
      ++countOfPatterns;
      left = right + 1;
    }
    else if (symbol == joker)
      ++left;
    ++right;
  }

  if (left != right)
  {
    std::string substring = pattern.substr(left, right - left);
    ++countOfPatterns;
    if (indices.find(substring) == indices.end())
      indices[substring] = {left};
    else
      indices[substring].push_back(left);
  }

  return indices;
};



Vertex *createTrie(std::string pattern, char joker)
{
  Vertex *root = new Vertex();

  for (auto elem : getPatterns(pattern, joker))
  {
    Vertex *current = root;

    for (size_t i = 0; i < elem.first.size(); ++i)
    {
      Vertex *previous = current;
      if (current->child.find(elem.first[i]) == current->child.end())
        current->child[elem.first[i]] = new Vertex(elem.first[i], previous);
      current = current->child[elem.first[i]];

      if (elem.first.size() - 1 == i)
      {
        current->isTerminal = true;
        current->number = elem.second;
        current->stringLen = elem.first.size();
      }
    }
  }

  std::queue<Vertex *> queue;
  queue.push(root);

  while (queue.size())
  {
    Vertex *current = queue.front();
    queue.pop();

    for (auto elem : current->child)
    {
      queue.push(elem.second);
    }

    if (current->parent != nullptr)
    {
      Vertex *suffix = current->parent->suffixLink;
      char vertex = current->vertex;

      while (suffix != nullptr && suffix->child.find(vertex) == suffix->child.end())
        suffix = suffix->suffixLink;

      if (suffix != nullptr)
        current->suffixLink = suffix->child[vertex];
      else
        current->suffixLink = root;

      if (current->suffixLink->isTerminal)
        current->terminalLink = current->suffixLink;
    }
  }

  return root;
}



void freeMemory(Vertex *root)
{
  for (auto elem : root->child)
  {
    freeMemory(elem.second);
  }
  delete root;
}

std::set<std::pair<int, std::vector<int>>> ahoCorasick(std::string text, std::string patterns, char joker)
{
  std::set<std::pair<int, std::vector<int>>> result;
  Vertex *root = createTrie(patterns, joker);

  Vertex *current = root;
  for (size_t i = 0; i < text.size(); ++i)
  {
    while (true)
    {
      Vertex *terminal = current->terminalLink;
      while (terminal != nullptr)
      {
        result.insert({i - terminal->stringLen, terminal->number});
        terminal = terminal->terminalLink;
      }

      if (current->child.find(text[i]) != current->child.end())
      {
        current = current->child[text[i]];
        if (current->isTerminal)
          result.insert({i - current->stringLen + 1, current->number});
        break;
      }
      else if (current == root)
        break;
      else
        current = current->suffixLink;
    }
  }

  freeMemory(root);

  return result;
}



int main()
{
  std::string text, pattern;
  char joker;

  std::cin >> text >> pattern >> joker;

  auto result = ahoCorasick(text, pattern, joker);

  int lastPos = text.size() - pattern.size();
  std::map<int, int> counter;
  for (auto pair : result)
  {
    for (auto number : pair.second)
    {
      int key = pair.first - number;
      if (0 <= key && key <= lastPos)
      {
          if (counter.find(key) == counter.end()){
              counter[key] = 1;
          }else{
                ++counter[key];
          }
      }
    }
  }

  for (auto elem : counter) {
    if (elem.second == countOfPatterns)
    std::cout << elem.first + 1 << '\n';
  }

  return 0;
}
