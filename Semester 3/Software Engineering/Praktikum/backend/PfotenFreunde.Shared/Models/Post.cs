using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Post
{
    public Post()
    {
        PicturePosts = new HashSet<PicturePost>();
    }

    public int Id { get; set; }
    public DateTime PostedAt { get; set; }
    public string Message { get; set; } = null!;
    public int UserId { get; set; }
    public int ChronicleId { get; set; }

    [JsonIgnore]
    public virtual Chronicle Chronicle { get; set; } = null!;
    [JsonIgnore]
    public virtual User User { get; set; } = null!;
    [JsonIgnore]
    public virtual ICollection<PicturePost> PicturePosts { get; set; }
}
