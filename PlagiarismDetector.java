import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Scanner;


/* Assumption: plagiarism broken up by line will be detected
 *
 * i.e. file1:                  file2:
 *      go for a jog            go
 *                              for
 *                              a 
 *                              jog
 * 
 * counts as plagiarism. 
 */
public class PlagiarismDetector {

    private String normalizer;
    private HashSet<String> synonyms;
    private ArrayList<String> file1;
    private ArrayList<String> file2;

    public PlagiarismDetector(String synonyms, String filename1, String filename2) {
        this.synonyms = loadSynonyms(synonyms);
        this.normalizer = getSynonymInstance();
        this.file1 = loadWords(filename1);
        this.file2 = loadWords(filename2);
        this.normalizeSynonyms();
    }

    private ArrayList<String> loadWords(String filename) {
        ArrayList<String> words = new ArrayList<String>();
        Scanner input = null;
        try {
            input = new Scanner(new File(filename));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        while (input.hasNext()) {
            words.add(input.next());
        }
        return words;
    }

    private HashSet<String> loadSynonyms(String filename) {
        HashSet<String> synonyms = new HashSet<String>();
        Scanner input = null;
        try {
            input = new Scanner(new File(filename));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        while (input.hasNext()) {
            synonyms.add(input.next());
        }
        return synonyms;
    }

    // gets a representative synonym to replace all other synonyms
    private String getSynonymInstance() {
        Iterator<String> itr = this.synonyms.iterator();
        if(itr.hasNext()){
            return itr.next();
        }
        return null;
    }

    // replaces all words that are synonyms in file1 & file2 to a default synonym word
    private void normalizeSynonyms() {
        for (int i = 0; i < this.file1.size(); ++i) {
            if (this.synonyms.contains(this.file1.get(i))) {
                this.file1.set(i, this.normalizer);
            }
        }
        for (int i = 0; i < this.file2.size(); ++i) {
            if (this.synonyms.contains(this.file2.get(i))) {
                this.file2.set(i, this.normalizer);
            }
        }
    }

    // returns the percent of tuples that appear in file1 that are also in file2
    // runtime of O(i*j*k) where n is the size of file1, m of file2, and l of tuplesize
    public int detect(int tupleSize) {
        int count = 0;
        int file1Tuples = this.file1.size() - tupleSize + 1;
        int file2Tuples = this.file2.size() - tupleSize + 1;
        for (int i = 0; i < file1Tuples; ++i) {
            for(int j = 0; j < file2Tuples; ++j) {
                for(int k = 0; k < tupleSize; ++k) {
                    if( ! this.file1.get(i+k).equals(file2.get(j+k))) {
                        break;
                    }
                    if (k == tupleSize - 1 ) {
                        ++count;
                    }
                }
            }
        }
        // Assumption: tupleSize is smaller than word count in files
        return 100*count/file1Tuples;
    }


    public static void main(String[] args) {
        int tupleSize = 3;
        if(args.length < 3) {
            System.out.println("Incorrect number of arguments");
            System.out.println("args: Synonym File, File1, File2, [TupleSize]");
            return;
        } else if (args.length == 4) {
            tupleSize = Integer.parseInt(args[3]);
        }
        PlagiarismDetector detector = new PlagiarismDetector(args[0], args[1], args[2]);
        int percent = detector.detect(tupleSize);
        System.out.println(percent + "%");
    }
}