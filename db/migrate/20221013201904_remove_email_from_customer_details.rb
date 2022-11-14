# frozen_string_literal: true

class RemoveEmailFromCustomerDetails < ActiveRecord::Migration[7.0]
  def change
    remove_column :customer_details, :email, :string
  end
end
