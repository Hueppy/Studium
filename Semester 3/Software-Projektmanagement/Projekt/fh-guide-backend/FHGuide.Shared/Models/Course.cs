using System.Text.Json.Serialization;

namespace FHGuide.Shared.Models;

public partial class Course
{
    public Course()
    {
        Appointments = new HashSet<Appointment>();
        RoadmapItems = new HashSet<RoadmapItem>();
        Zooms = new HashSet<Zoom>();
    }

    public int CourseId { get; set; }
    public string Name { get; set; } = null!;
    public string? Description { get; set; }
    public string Room { get; set; } = null!;
    public int? ZoomId { get; set; }
    public int ModuleId { get; set; }

    [JsonIgnore]
    public virtual Module? Module { get; set; } = null!;
    [JsonIgnore]
    public virtual Zoom? Zoom { get; set; }
    [JsonIgnore]
    public virtual ICollection<Appointment> Appointments { get; set; }
    [JsonIgnore]
    public virtual ICollection<RoadmapItem> RoadmapItems { get; set; }
    [JsonIgnore]
    public virtual ICollection<Zoom> Zooms { get; set; }
}
