using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class InstitutionController : ControllerBase
{
	private PfotenFreundeContext context;

	public InstitutionController(PfotenFreundeContext context)
	{
		this.context = context;
	}
	
    /// <summary>
    /// Gets all institutions
    /// </summary>
    [HttpGet]
    public IEnumerable<Institution> GetAll()
    {
        return this.context.Institutions;
    }
	
    /// <summary>
    /// Gets information about the institution
    /// </summary>
    /// <response code="404">Institution not found</response>
    [HttpGet("{id}")]
    public async Task<ActionResult<Institution>> Get(int id)
    {
        var institution = await this.context.Institutions.FindAsync(id);
		
		if (institution == null)
		{
			return NotFound();
		}
		
		return institution;
    }

    /// <summary>
    /// Creates a new institution
    /// </summary>
    [HttpPost]
    public async Task<int> Post(Institution institution)
    {
		institution.Id = 0;
		var entry = await this.context.Institutions.AddAsync(institution);
		
		await this.context.SaveChangesAsync();

		return entry.Entity.Id;
    }

    /// <summary>
    /// Updates information of an institution
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    [HttpPatch("{id}")]
    public async Task Patch(int id, Institution institution)
    {
		institution.Id = id;
		var entry = this.context.Institutions.Update(institution);

		await this.context.SaveChangesAsync();
    }
}
