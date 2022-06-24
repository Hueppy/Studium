using System.Text.Json.Serialization;

namespace FHGuide.Shared.Models;

public partial class ScheduleCourse
{
    public int ScheduleId { get; set; }
    public int CourseId { get; set; }

    [JsonIgnore]
    public virtual Course? Course { get; set; } = null!;
    [JsonIgnore]
    public virtual Schedule? Schedule { get; set; } = null!;
}
