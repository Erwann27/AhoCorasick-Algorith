#!/bin/python3
# returns a list containing results with specific alphabet length
def search_alph_length(tab, length, algo):
  result = [];
  for couples in tab:
    if (int(couples[3]) == length and couples[0] == algo):
      result.append(couples);
  return result;

# returns a list containing results with specific word length
def search_word_length(tab, length, algo):
  result = [];
  for couples in tab:
    if (int(couples[1]) == length and couples[0] == algo):
        result.append(couples);
  return result;

import matplotlib.pyplot as plt
import itertools 

file = open("result.txt", "r");
result = []
for algo, time in itertools.zip_longest(*[file]*2):
    content = algo.split();
    value = time.split();
    result.append((content[0], content[1], content[2], content[3], float(value[0])));


word_length = [5, 15, 30];
alph_length = [2, 4, 20, 70];
algo = ["hash", "mat"];

# Courbes par algorithme pour chaque taille d'alphabet

for alph in alph_length:
    tmp = search_alph_length(result, alph, "hash");
    tmp2 = search_alph_length(result, alph, "mat");
    x = word_length;
    mat = []
    hash = []
    for mean in tmp:
        hash.append(mean[4]);
    for mean in tmp2:
        mat.append(mean[4]);
    plt.plot(x, hash, label='hash');
    plt.plot(x, mat, label='mat');
    plt.legend()
    plt.title("Evolution des algos pour un alphabet de taille " + str(alph));
    plt.xlabel("word length");
    plt.ylabel("running time");
    plt.savefig("Courbes/alphabet_" + str(alph));
    plt.close()

# Courbes par algorithme pour chaque longueur de mots

for word in word_length:
    tmp = search_word_length(result, word, "hash");
    tmp2 = search_word_length(result, word, "mat");
    x = alph_length;
    mat = []
    hash = []
    for mean in tmp:
        hash.append(mean[4]);
    for mean in tmp2:
        mat.append(mean[4]);
    plt.plot(x, hash, label='hash');
    plt.plot(x, mat, label='mat');
    plt.legend()
    plt.title("Evolution des algos pour un alphabet de taille " + str(word));
    plt.xlabel("word length");
    plt.ylabel("running time");
    plt.savefig("Courbes/word_" + str(word));
    plt.close()
