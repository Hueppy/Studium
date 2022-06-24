using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class PictureUser
{
    public int Id { get; set; }
    public int UserId { get; set; }

    [JsonIgnore]
    public virtual Picture Picture { get; set; } = null!;
    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
