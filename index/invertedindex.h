#ifndef INVERTEDINDEX_H
#define INVERTEDINDEX_H

#include "common/types.h"
#include "tfidf.h"

namespace sse {

class InvertedIndex
{
public:
    InvertedIndex(uint vocabularySize);
    void addSample(const Vec_f32_t &sample);
    void createIndex(const TF_interface &tf, const IDF_interface &idf);
    void save(const std::string& filename);
    void load(const std::string& filename);

    inline const std::vector<uint>& ft() const { return _ft; }
    inline const std::vector<std::vector<std::pair<uint, float> > >& invertList() const { return _invertedList; }
    inline uint numOfDocuments() const { return _numOfDocuments; }
private:
    void init(uint numOfWords = 0);

    uint _numOfWords;

    //Document-level inverted index
    //term t : [0, vocabularySize)
    //_ft: a count ft of the documents containing t
    std::vector<uint> _ft;
    //_invertedList: Inverted list for terms:
    // the entry for each term t is composed of a document identifier d and a document frequency f_dt
    std::vector<std::vector<std::pair<uint, float> > > _invertedList;
    // tf-idf weights
    //_weightList[term_id][list_id] = tf-idf(_invertedList[term_id][list_id])
    std::vector<std::vector<float> > _weightList;

    uint _numOfDocuments;
};

}


#endif // INVERTEDINDEX_H