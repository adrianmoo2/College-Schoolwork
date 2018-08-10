package EDUCrawler;

import java.io.*;
import java.util.HashSet;
import java.util.LinkedList;

import org.jsoup.Jsoup;
import org.jsoup.Connection;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;


public class Crawler {
	private int MAX_PAGES;
	private int MAX_HOPS;
	private String SEED_FILE;
	private String OUT_DIR;
	
	// Using HashSet and LinkedList purely for performance
    private HashSet<String> visitedUrls;
    private LinkedList<String> seedUrls;
    
    Crawler(String seedfile,
	int maxpgs,
	int maxhops,
	String Dir)
    {
    	SEED_FILE = seedfile;
    	MAX_PAGES = maxpgs;
    	MAX_HOPS = maxhops;
    	OUT_DIR = Dir;
    	visitedUrls = new HashSet<>();
    	seedUrls = new LinkedList<>();
    	// Assuming seed file is set with each URL on a new line
    	try
		{
		    BufferedReader reader = new BufferedReader(new FileReader(SEED_FILE));
		    System.out.printf("Reading '%s'\n", SEED_FILE);
		    String line;
		    while ((line = reader.readLine()) != null)
		    {
		    	System.out.println(line);
		    	this.seedUrls.add(line);
		    }
		    reader.close();
	    }
    	catch (Exception e)
    	{
    		System.out.printf("Error trying to read '%s'.", SEED_FILE);
		    System.exit(-1);
    	}
    }
    
    private String nextUrl() // Go through seed list
    {
        String nextUrl;
        do
        {
            nextUrl = this.seedUrls.remove(0);
        } while(this.visitedUrls.contains(nextUrl));
        return nextUrl;
    }
    
    public void getLinks(String URL, int depth) {
        if ((!this.visitedUrls.contains(URL)) && (depth < this.MAX_HOPS) && (this.visitedUrls.size() < this.MAX_PAGES)) {
            try {
            	System.out.printf("Parsing: '%s' at depth '%d'\n", URL, depth);
            	visitedUrls.add(URL);
            	
            	Connection.Response response = Jsoup.connect(URL).execute();
                Document doc = response.parse();
                
                String formattedUrl = URL.replace(':', '_');
                formattedUrl = formattedUrl.replace('/', '_');
                formattedUrl = formattedUrl.replace('?', '_');
                File f = new File(OUT_DIR+"/"+formattedUrl+".html");
                BufferedWriter out = new BufferedWriter(new FileWriter(f));
                out.write(doc.html());
                out.close();
                Elements links = doc.select("a[href]");

                depth++;
                for (Element page : links) {
                    getLinks(page.attr("abs:href"), depth);
                }
            } 
            catch (Exception e) 
            {
            	//Ignore non html pages
            }
        }
    }
    
	public static void main(String[] args) { 	
		if (args.length == 4)
		{
			// Create crawler with given arguments
			String seedfile = args[0];
			int maxpgs = Integer.parseInt(args[1]);
			int maxhops = Integer.parseInt(args[2]);
			String Dir = args[3];
			Crawler crawler = new Crawler(seedfile, maxpgs, maxhops, Dir);
			
			while((crawler.visitedUrls.size() < maxpgs) && (!crawler.seedUrls.isEmpty()))
			{
				crawler.getLinks(crawler.nextUrl(), 0);
			}
		}
		else
		{
			System.out.println("Error: Not enough arguments.");
			return;
		}
	}
}
