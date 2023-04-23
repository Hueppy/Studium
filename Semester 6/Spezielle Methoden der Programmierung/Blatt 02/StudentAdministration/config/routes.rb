Rails.application.routes.draw do
  #root 'students#index'

  resources :students
  resources :lecturer
  resources :course
end
