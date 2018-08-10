package buildIndex;

import org.apache.lucene.analysis.Analyzer;
import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.document.TextField;
import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.DirectoryReader;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.queryparser.classic.ParseException;
import org.apache.lucene.store.Directory;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.store.LockObtainFailedException;

import java.io.*;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;


public class LuceneSearcher {
		
	public static final String FILES_TO_INDEX_DIRECTORY = "Results";  //replace with directory containing HTML files from PART A
	public static final String INDEX_DIRECTORY = "Index"; //replace with directory we wish to index to

	public static void main(String[] args) throws Exception {
		createIndex();
	}
	

	public static void createIndex() throws CorruptIndexException, LockObtainFailedException, IOException, ParseException {
		

		Analyzer analyzer = new StandardAnalyzer();
		IndexWriterConfig config = new IndexWriterConfig(analyzer);
		Path path = Paths.get(INDEX_DIRECTORY);
		Directory directory = FSDirectory.open(path);
        
        if(!DirectoryReader.indexExists(directory))
        {
            IndexWriter indexWriter = new IndexWriter(directory, config);
			File dir = new File(FILES_TO_INDEX_DIRECTORY);
			File[] files = dir.listFiles();
			for (File file : files) {
				try
				{
					org.jsoup.nodes.Document doc = Jsoup.parse(file, "UTF-8");
					Document index = new Document();
		            index.add(new TextField("title", doc.title(), Field.Store.YES));
		            index.add(new TextField("content", doc.body().text(), Field.Store.YES));
					index.add(new TextField("url", "Results/"+file.getName(), Field.Store.YES));
					
					Elements metaTags = doc.getElementsByTag("meta");
					for (Element metaTag : metaTags) {
						String content = metaTag.attr("content");
						String name = metaTag.attr("name");
						
						if("date".equals(name) || "creation-date".equals(name) || "creation date".equals(name) || "creation".equals(name) || "date-created".equals(name) || "date created".equals(name)) {
							index.add(new TextField("creationDate", content, Field.Store.YES));
						}
						if("author".equals(name)) {
							index.add(new TextField("author", content, Field.Store.YES));
						}
						if("description".equals(name)) {
							index.add(new TextField("description", content, Field.Store.YES));
						}
						if("keywords".equals(name)) {
							index.add(new TextField("keywords", content, Field.Store.YES));
						}
					}
					
		            indexWriter.addDocument(index);
					
			    }
				catch (Exception e)
				{
					System.out.printf("Error trying to read file.");
				    System.exit(-1);
				}
			}
			indexWriter.close();
        }
		
	}

}
