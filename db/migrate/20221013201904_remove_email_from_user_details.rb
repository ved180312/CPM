# frozen_string_literal: true

class RemoveEmailFromUserDetails < ActiveRecord::Migration[7.0]
  def change
    remove_column :user_details, :email, :string
  end
end
