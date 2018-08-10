package buildIndex.lucenesearch;

public class Article {

	public int id;
    float score;
    public String url;
    public String title;
    public String body;

    public Article(){}

    public Article(int id, String url, float score, String title, String body) {
        this.id = id;
        this.url = url;
        this.score = score;
        this.title = title;
        this.body = body;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
    
    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }
    
    
    public float getScore() {
        return score;
    }

    public void setScore(float score) {
        this.score = score;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getBody() {
        return body;
    }

    public void setBody(String body) {
        this.body = body;
    }

    @Override
    public String toString() {
        return String.format("Article[id=%d, score=%.3f title=%s, body=%s]", id, score, title, body);
    }
}
