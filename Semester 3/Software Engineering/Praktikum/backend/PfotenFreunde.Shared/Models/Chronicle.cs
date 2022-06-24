using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Chronicle
{
    public Chronicle()
    {
        Posts = new HashSet<Post>();
    }

    public int Id { get; set; }

    [JsonIgnore]
    public virtual ICollection<Post> Posts { get; set; }
}
