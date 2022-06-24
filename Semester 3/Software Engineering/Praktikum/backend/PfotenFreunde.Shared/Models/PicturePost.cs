using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class PicturePost
{
    public int Id { get; set; }
    public int PostId { get; set; }

    [JsonIgnore]
    public virtual Picture Picture { get; set; } = null!;
    [JsonIgnore]
    public virtual Post Post { get; set; } = null!;
}
