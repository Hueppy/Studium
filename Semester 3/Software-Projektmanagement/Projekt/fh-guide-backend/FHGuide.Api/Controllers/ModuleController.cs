using Microsoft.AspNetCore.Mvc;
using FHGuide.Shared.Models;
using FHGuide.Shared.Contexts;

namespace FHGuide.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class ModuleController : ControllerBase
{
	private readonly FHGuideContext DbContext;

    public ModuleController(FHGuideContext dbContext)
    {
		this.DbContext = dbContext;
    }

	/// <summary>
	/// Get all modules
	/// </summary>
	[HttpGet]
	public IEnumerable<Module> Get()
	{
        return this.DbContext.Modules;
	}

	/// <summary>
	/// Get Faq of module
	/// </summary>
	[HttpGet("{id}/faq")]
	public IEnumerable<Faq> GetFaq(int id)
	{
		return this.DbContext.Faqs.Where(x => x.ModuleId == id);
	}

	/// <summary>
	/// Get ratings of module
	/// </summary>
	[HttpGet("{id}/rating")]
	public IEnumerable<Rating> GetRating(int id)
	{
		return this.DbContext.Ratings.Where(x => x.ModuleId == id);
	}

	/// <summary>
	/// Get courses of module
	/// </summary>
	[HttpGet("{id}/course")]
	public IEnumerable<Course> GetCourse(int id)
	{
		return this.DbContext.Courses.Where(x => x.ModuleId == id);
	}

	/// <summary>
	/// Create a new module
	/// </summary>
	[HttpPost]
	public async Task<int> Post(Module module)
	{
        module.ModuleId = 0;

        var entry = await this.DbContext.Modules.AddAsync(module);
        await this.DbContext.SaveChangesAsync();

        return entry.Entity.ModuleId;
	}

	/// <summary>
	/// Update module with specified id
	/// </summary>
	[HttpPatch("{id}")]
	public async Task Patch(int id, Module module)
	{
		module.ModuleId = id;

        this.DbContext.Update(module);
        await this.DbContext.SaveChangesAsync();
	}

	/// <summary>
	/// Delete module with specified id
	/// </summary>
	[HttpDelete("{id}")]
	public async Task<ActionResult> Delete(int id)
	{
		var item = await this.DbContext.Modules.FindAsync(id);

		if (item == null)
		{
			return NotFound();
		}

		this.DbContext.Modules.Remove(item);
        await this.DbContext.SaveChangesAsync();
		return Ok();
	}
}
