using System.Text.Json.Serialization;

namespace PfotenFreunde.Shared.Models;

public partial class Rating
{
    public int Id { get; set; }
    public RatingType Type { get; set; }
    public int UserId { get; set; }
    public int SenderId { get; set; }

    [JsonIgnore]
    public virtual User Sender { get; set; } = null!;
    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
