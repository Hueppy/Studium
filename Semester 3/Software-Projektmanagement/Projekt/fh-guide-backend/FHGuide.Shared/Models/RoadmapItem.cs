using System.Text.Json.Serialization;

namespace FHGuide.Shared.Models;

public partial class RoadmapItem
{
    public int RoadmapItemId { get; set; }
    public string Week { get; set; } = null!;
    public string Name { get; set; } = null!;
    public string Style { get; set; } = null!;
    public string? Material { get; set; }
    public int CourseId { get; set; }

    [JsonIgnore]
    public virtual Course? Course { get; set; } = null!;
}
