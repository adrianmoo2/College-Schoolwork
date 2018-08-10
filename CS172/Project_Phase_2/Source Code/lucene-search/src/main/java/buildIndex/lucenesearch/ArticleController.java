package buildIndex.lucenesearch;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.queryparser.classic.MultiFieldQueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.ScoreDoc;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.springframework.web.bind.annotation.*;
import org.apache.lucene.queryparser.classic.ParseException;

import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.List;

@RestController
@RequestMapping("/api")
@CrossOrigin("*")
public class ArticleController {
	public static final String INDEX_DIRECTORY = "Index"; //replace with directory we wish to index to
	
    static List<Article> articles;
    

    @GetMapping("/articles")
    public List<Article> searchArticles(
            @RequestParam(required=false, defaultValue="") String querystr) throws IOException, ParseException {
        if (querystr.isEmpty())
            return articles;
        List<Article> matches = new ArrayList<>();
       
		Analyzer analyzer = new StandardAnalyzer();
		Path path = Paths.get(INDEX_DIRECTORY);
		Directory directory = FSDirectory.open(path);
        
        DirectoryReader indexReader = DirectoryReader.open(directory);
        IndexSearcher indexSearcher = new IndexSearcher(indexReader);

        String[] fields = {"title", "content", "description", "author", "keywords"};
        Map<String, Float> boosts = new HashMap<String, Float>();
        boosts.put(fields[0], 1.0f);
        boosts.put(fields[1], 0.5f);
        boosts.put(fields[2], 0.8f);
        boosts.put(fields[3], 0.9f);
        boosts.put(fields[4], 0.9f);
        MultiFieldQueryParser parser = new MultiFieldQueryParser(fields, analyzer, boosts);
        Query query = parser.parse(querystr);
        System.out.println(query.toString());
        int topHitCount = 20;
        ScoreDoc[] hits = indexSearcher.search(query, topHitCount).scoreDocs;

        // Iterate through the results:
        for (int rank = 0; rank < hits.length; ++rank) {
            Document hitDoc = indexSearcher.doc(hits[rank].doc);
            matches.add(new Article((rank + 1), hitDoc.get("url"), hits[rank].score, hitDoc.get("title"),
            		hitDoc.get("content")));
        }
        indexReader.close();
        directory.close();
        return matches;
    }
}
