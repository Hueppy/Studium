using System.Text.Json.Serialization;

namespace FHGuide.Shared.Models;

public partial class Rating
{
    public Rating()
    {
        RatingValues = new HashSet<RatingValue>();
    }

    public int RatingId { get; set; }
    public string? Description { get; set; }
    public int AccountId { get; set; }
    public int ModuleId { get; set; }

    [JsonIgnore]
    public virtual Account? Account { get; set; } = null!;
    [JsonIgnore]
    public virtual Module? Module { get; set; } = null!;
    [JsonIgnore]
    public virtual ICollection<RatingValue> RatingValues { get; set; }
}
