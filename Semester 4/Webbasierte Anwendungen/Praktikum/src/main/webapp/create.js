async function doProjectSubmit(event) {
    event.preventDefault()

    const project = new Project()

    project.title = document.getElementById('title')?.value
    project.shortDescription = document.getElementById('short_description')?.value
    project.longDescription = document.getElementById('long_description')?.value

    console.log(project)

    const api = new ProjectApi()
    await api.create(project)


    const projects = await api.all()
    const created = projects.pop();
    window.location.href = `http://localhost:8080/Projectportal-1.0-SNAPSHOT/project.html?id=${created.id}`
}

window.addEventListener('load', async function () {
    const form = document.getElementById('createform');
    form.addEventListener('submit', doProjectSubmit);
})