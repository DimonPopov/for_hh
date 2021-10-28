#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <set>

class Vertex
{
public:
  Vertex(char vertex_ = '?', Vertex *parent_ = nullptr) : vertex(vertex_), parent(parent_) {}
  char vertex = '?';
  bool isTerminal = false;
  Vertex *parent = nullptr;
  Vertex *suffixLink = nullptr;
  Vertex *terminalLink = nullptr;
  int number = 0;
  int stringLen = 0;
  std::map<char, Vertex *> child;
};

Vertex *createTrie(std::vector<std::string> pattern)
{
  Vertex *root = new Vertex();
  int count = 0;

  for (auto elem : pattern)
  {
    Vertex *current = root;
    for (size_t i = 0; i < elem.size(); ++i)
    {
      Vertex *previous = current;
      if (current->child.find(elem[i]) == current->child.end())
        current->child[elem[i]] = new Vertex(elem[i], previous);
      current = current->child[elem[i]];

      if (elem.size() - 1 == i)
      {
        current->isTerminal = true;
        current->number = count++;
        current->stringLen = elem.size();
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

std::set<std::pair<int, int>> ahoCorasick(std::string text, std::vector<std::string> patterns)
{
  std::set<std::pair<int, int>> result;
  Vertex *root = createTrie(patterns);

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
  std::string text;
  int numbers;
  std::vector<std::string> patterns;

  std::cin >> text >> numbers;

  for (int i = 0; i < numbers; ++i)
  {
    std::string temp;
    std::cin >> temp;
    patterns.push_back(temp);
  }

  auto result = ahoCorasick(text, patterns);

  for (auto elem : result)
  {
    std::cout << elem.first + 1 << ' ' << elem.second + 1 << '\n';
  }

  return 0;
}